#include "websockets.h" // includes the "http.h" header

#include <stdio.h>
#include <stdlib.h>

/* ******************************
The Websocket echo implementation
*/

void ws_open(ws_s * ws) {
  fprintf(stderr, "Opened a new websocket connection (%p)\n", (void * )ws);
}

void ws_echo(ws_s * ws, char * data, size_t size, uint8_t is_text) {
  // echos the data to the current websocket
  websocket_write(ws, data, size, is_text);
}

void ws_shutdown(ws_s * ws) { websocket_write(ws, "Shutting Down", 13, 1); }

void ws_close(ws_s * ws) {
  fprintf(stderr, "Closed websocket connection (%p)\n", (void * )ws);
}

/* ********************
The HTTP implementation
*/

void on_request(http_request_s * request) {
  http_response_s * response = http_response_create(request);
  http_response_log_start(response); // logging
  // websocket upgrade.
  if (request->upgrade) {
    websocket_upgrade(.request = request, .on_message = ws_echo,
                      .on_open = ws_open, .on_close = ws_close, .timeout = 40,
                      .on_shutdown = ws_shutdown, .response = response);
    return;
  }
  // HTTP response
  http_response_write_body(response, "Hello World! Why not test me using Websockets\x3f", 46);
  http_response_finish(response);
}

/****************
The main function
*/

#define THREAD_COUNT 1
int main(void) {
  const char* public_folder = NULL;
  http_listen("3000", NULL, .on_request = on_request,
               .public_folder = public_folder, .log_static = 1);
  facil_run(.threads = THREAD_COUNT);
  return 0;
}
