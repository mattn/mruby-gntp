#include <mruby.h>
#include <mruby/string.h>
#include "md5.h"
#include "growl.h"

extern void gntp_notify_send(const char*, const char*, const char*, const char*);
extern void* gntp_create(const char*, const char*, const char*, const char*);
extern void gntp_register(void*, const char*);
extern void gntp_notify(void*, const char*, const char*, const char*, const char*, const char*);
extern void gntp_release(void*);

static struct RClass *_class_gntp;

static mrb_value
mrb_gntp_notify_send(mrb_state *mrb, mrb_value self)
{
  mrb_value arg = mrb_nil_value();

  mrb_get_args(mrb, "o", &arg);
  if (mrb_nil_p(arg) || (mrb_type(arg) != MRB_TT_STRING && mrb_type(arg) != MRB_TT_HASH)) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid argument");
  }

  if (mrb_type(arg) == MRB_TT_STRING) {
    growl("127.0.0.1:23053", "mruby-gntp", "notify", "notification", RSTRING_PTR(arg), NULL, NULL, NULL);
  } else {
  }


  return mrb_nil_value();
}

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

/*********************************************************
 * register
 *********************************************************/

void
mrb_mruby_gntp_gem_init(mrb_state* mrb) {
  _class_gntp = mrb_define_module(mrb, "GNTP");
  mrb_define_class_method(mrb, _class_gntp, "notify", mrb_gntp_notify_send, ARGS_REQ(1));

  mrb_define_method(mrb, _class_gntp, "initialize", mrb_gntp_init, ARGS_REQ(1));
  mrb_define_method(mrb, _class_gntp, "register", mrb_gntp_register, ARGS_REQ(1));
  mrb_define_method(mrb, _class_gntp, "notify", mrb_gntp_register, ARGS_REQ(1));
}

/* vim:set et ts=2 sts=2 sw=2 tw=0: */
