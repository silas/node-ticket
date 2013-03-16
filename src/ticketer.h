#ifndef TICKETER_H
#define TICKETER_H

#include <node.h>
#include <v8.h>
#include <time.h>

#define SEQUENCE_BITS 16
#define SERVER_BITS 13

#define TIME_LEFT_SHIFT SEQUENCE_BITS + SERVER_BITS
#define SERVER_LEFT_SHIFT SEQUENCE_BITS
#define SEQUENCE_MASK (-1L ^ (-1L << SEQUENCE_BITS))

#define BUFFER_SIZE 21

class Ticketer : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> target);

 private:
  Ticketer();
  ~Ticketer();

  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  static v8::Handle<v8::Value> Get(const v8::Arguments& args);
  time_t current_time_;
  time_t last_time_;
  long long sequence_;
  long long id_;
};

#endif
