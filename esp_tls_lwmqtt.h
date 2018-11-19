#ifndef ESP_TLS_LWMQTT_H
#define ESP_TLS_LWMQTT_H

#include <lwmqtt.h>
#include "mbedtls/platform.h"
#include "mbedtls/net_sockets.h"
#include "mbedtls/esp_debug.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/error.h"
#include "mbedtls/certs.h"
#include <esp_log.h>
#include <sdkconfig.h>

extern const uint8_t server_root_cert_pem_start[] asm("_binary_server_root_cert_pem_start");
extern const uint8_t server_root_cert_pem_end[]   asm("_binary_server_root_cert_pem_end");

/**
 * The tls lwmqtt network object for the esp platform.
 */
typedef struct {
  mbedtls_entropy_context entropy;
  mbedtls_ctr_drbg_context ctr_drbg;
  mbedtls_ssl_context ssl;
  mbedtls_ssl_config conf;
  mbedtls_x509_crt cacert;
  mbedtls_x509_crt clientcert;
  mbedtls_pk_context clientkey;
  mbedtls_net_context socket;
} esp_tls_lwmqtt_network_t;

/**
 * Initiate a connection to the specified remote host.
 */
lwmqtt_err_t esp_tls_lwmqtt_network_connect(esp_tls_lwmqtt_network_t *network, char *host, char *port);

/**
 * Wait until the socket is connected or a timeout has been reached.
 */
lwmqtt_err_t esp_tls_lwmqtt_network_wait(esp_tls_lwmqtt_network_t *network, bool *connected, uint32_t timeout);

/**
 * Terminate the connection.
 */
void esp_tls_lwmqtt_network_disconnect(esp_tls_lwmqtt_network_t *network);

/**
 * Will set available to the available amount of data in the underlying network buffer.
 */
lwmqtt_err_t esp_tls_lwmqtt_network_peek(esp_tls_lwmqtt_network_t *network, size_t *available, uint32_t timeout);

/**
 * Will wait for a socket until data is available or the timeout has been reached.
 */
lwmqtt_err_t esp_tls_lwmqtt_network_select(esp_tls_lwmqtt_network_t *network, bool *available, uint32_t timeout);

/**
 * The tls lwmqtt network read callback for the esp platform.
 */
lwmqtt_err_t esp_tls_lwmqtt_network_read(void *ref, uint8_t *buf, size_t len, size_t *read, uint32_t timeout);

/**
 * The tls lwmqtt network write callback for the esp platform.
 */
lwmqtt_err_t esp_tls_lwmqtt_network_write(void *ref, uint8_t *buf, size_t len, size_t *sent, uint32_t timeout);

#endif  // ESP_LWMQTT_H
