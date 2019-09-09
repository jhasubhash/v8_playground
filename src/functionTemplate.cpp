#include "functiontemplate.h"
#include <iostream>
#include "v8.h"
using namespace v8;

static void LogCallback(const FunctionCallbackInfo<Value>& args)
{
  std::cout<<"In LOG Callback"<<std::endl;
}

void runFunctionTemplate(Isolate* isolate){

    v8::Isolate::Scope isolate_scope(isolate);
    v8::HandleScope handle_scope(isolate);

    Local<ObjectTemplate> global = ObjectTemplate::New(isolate);
    Local<String> fn_name = String::NewFromUtf8(isolate, "log").ToLocalChecked();
    global->Set(fn_name,FunctionTemplate::New(isolate, LogCallback));

    // Create a new context.
    v8::Local<v8::Context> context = v8::Context::New(isolate, NULL, global);

    v8::Context::Scope context_scope(context);
    //call log from JS side
    {
      const char* csource = R"(
        log();
      )";
      v8::Local<v8::String> source = v8::String::NewFromUtf8(isolate, csource, v8::NewStringType::kNormal) .ToLocalChecked();
      v8::Local<v8::Script> script = v8::Script::Compile(context, source).ToLocalChecked();
      v8::Local<v8::Value> result = script->Run(context).ToLocalChecked(); 
    }
}