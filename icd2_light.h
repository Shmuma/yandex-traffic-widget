#ifndef __ICD2_LIGHT_H__
#define __ICD2_LIGHT_H__

/*
 * This is truncated version of file /usr/include/icd/dbus_api.h
 * I created it because of glib.h inclusion in the original file
 */
#ifdef __cplusplus
extern "C" {
#endif

#define ICD_DBUS_API_INTERFACE	"com.nokia.icd2"
#define ICD_DBUS_API_PATH	"/com/nokia/icd2"
#define ICD_DBUS_API_STATE_SIG	"state_sig"
#define ICD_DBUS_API_STATE_REQ	"state_req"


/** Connection state */
enum icd_connection_state {
  /** Network is or became disconnected */
  ICD_STATE_DISCONNECTED = 0,
  /** Establishing network connection */
  ICD_STATE_CONNECTING = 1,
  /** Network is connected */
  ICD_STATE_CONNECTED = 2,
  /** Network is being disconnected */
  ICD_STATE_DISCONNECTING = 3,
  /** service provider module informs about enabled limited connectivity */
  ICD_STATE_LIMITED_CONN_ENABLED = 4,
  /** service provider module informs about disabled limited connectivity */
  ICD_STATE_LIMITED_CONN_DISABLED = 5,

  /** Network searching started */
  ICD_STATE_SEARCH_START = 8,
  /** Network searching stopped */
  ICD_STATE_SEARCH_STOP = 9,

  /** Internal network state, IP address(es) has/have been acquired */
  ICD_STATE_INTERNAL_ADDRESS_ACQUIRED = 15
};


#ifdef __cplusplus
}
#endif

#endif /* __ICD2_LIGHT_H__ */
