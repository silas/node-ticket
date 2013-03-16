#include <node.h>
#include "ticketer.h"

using namespace v8;

Ticketer::Ticketer() {};
Ticketer::~Ticketer() {};

void Ticketer::Init(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("Ticketer"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("get"),
      FunctionTemplate::New(Get)->GetFunction());

  Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("Ticketer"), constructor);
}

Handle<Value> Ticketer::New(const Arguments& args) {
  HandleScope scope;

  Ticketer* obj = new Ticketer();
  obj->id_ = args[0]->IsUndefined() ? 1 : args[0]->NumberValue();
  obj->Wrap(args.This());

  if (obj->id_ < 0 || obj->id_ > 8192) {
    ThrowException(Exception::TypeError(String::New("id must be an integer between 0 and 8192")));
    return scope.Close(Undefined());
  }

  return args.This();
}

Handle<Value> Ticketer::Get(const Arguments& args) {
  HandleScope scope;

  Ticketer* obj = ObjectWrap::Unwrap<Ticketer>(args.This());

  time(&obj->current_time_);

  if (obj->current_time_ != obj->last_time_) {
    obj->sequence_ = 0;
    obj->last_time_ = obj->current_time_;
  }

  ++obj->sequence_;

  if (obj->sequence_ > 65536) {
    ThrowException(Exception::Error(String::New("sequence overflow")));
    return scope.Close(Undefined());
  }

  long long result = ((long long)obj->current_time_ << TIME_LEFT_SHIFT)
    | (obj->id_ << SERVER_LEFT_SHIFT)
    | (obj->sequence_ & SEQUENCE_MASK);

  char buffer[BUFFER_SIZE];
  sprintf(buffer, "%lld", result);

  return scope.Close(String::New(buffer));
}
