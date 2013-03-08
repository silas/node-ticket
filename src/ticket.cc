#include <node.h>
#include "ticketer.h"

using namespace v8;

void InitAll(Handle<Object> target) {
  Ticketer::Init(target);
}

NODE_MODULE(ticket, InitAll)
