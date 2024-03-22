idf_component_register(SRCS "app_main.c"
                            "wifi/wifi_ap.c"
                            "wifi/wifi_sta.c"
               INCLUDE_DIRS "."
               REQUIRES esp_event esp_http_server esp_http_client esp_https_ota esp_wifi esp_partition mqtt bt 
                       			freertos spiffs nvs_flash driver vfs)
set(EXTRA_COMPONENT_DIRS    $ENV{IDF_PATH}/examples/common_components/protocol_examples_common
                            $ENV{IDF_PATH}/examples/bluetooth/esp_ble_mesh/common_components/example_init)
target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
