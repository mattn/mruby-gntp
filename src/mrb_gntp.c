#include <mruby.h>
#include <mruby/string.h>
#include <mruby/hash.h>
#include "md5.h"
#include "growl.h"
#include <stdio.h>

const char*
hash_value(mrb_state* mrb, mrb_value hash, const char* key, const char* defvalue) {
  mrb_sym vkey = mrb_intern_cstr(mrb, key);
  mrb_value r = mrb_hash_get(mrb, hash, mrb_symbol_value(vkey));
  if (!mrb_nil_p(r)) {
    return RSTRING_PTR(mrb_funcall(mrb, r, "to_s", 0, NULL));
  }
  return defvalue;
}

static mrb_value
mrb_gntp_notify_send(mrb_state *mrb, mrb_value self)
{
  mrb_value arg = mrb_nil_value();

  mrb_get_args(mrb, "o", &arg);
  switch (mrb_type(arg)) {
  case MRB_TT_STRING:
    growl("127.0.0.1:23053", "mruby-gntp", "notify", "notification", RSTRING_PTR(arg), NULL, NULL, NULL);
    break;
  case MRB_TT_HASH:
    growl(
      hash_value(mrb, arg, "server", "127.0.0.1:23053"),
      hash_value(mrb, arg, "application", "mruby-gntp"),
      hash_value(mrb, arg, "event", "notify"),
      hash_value(mrb, arg, "title", "notification"),
      hash_value(mrb, arg, "message", "hello world"),
      hash_value(mrb, arg, "icon", NULL),
      hash_value(mrb, arg, "password", NULL),
      hash_value(mrb, arg, "url", NULL));
    break;
  default:
    mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid argument");
    break;
  }

  return mrb_nil_value();
}

/*
static mrb_value
mrb_gntp_init(mrb_state *mrb, mrb_value self)
{
  return self;
}

static mrb_value
mrb_gntp_register(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
mrb_gntp_notify(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}
*/

/*********************************************************
 * register
 *********************************************************/

void
mrb_mruby_gntp_gem_init(mrb_state* mrb) {
  struct RClass* _class_gntp = mrb_define_module(mrb, "GNTP");
  mrb_define_class_method(mrb, _class_gntp, "notify", mrb_gntp_notify_send, ARGS_REQ(1));
  /*
  mrb_define_method(mrb, _class_gntp, "initialize", mrb_gntp_init, ARGS_REQ(1));
  mrb_define_method(mrb, _class_gntp, "register", mrb_gntp_register, ARGS_REQ(1));
  mrb_define_method(mrb, _class_gntp, "notify", mrb_gntp_notify, ARGS_REQ(1));
  */
}

void
mrb_mruby_gntp_gem_final(mrb_state* mrb) {
}

/* vim:set et ts=2 sts=2 sw=2 tw=0: */
