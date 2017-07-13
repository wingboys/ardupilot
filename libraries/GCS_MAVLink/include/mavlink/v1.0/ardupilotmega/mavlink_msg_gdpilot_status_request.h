// MESSAGE GDPILOT_STATUS_REQUEST PACKING

#define MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST 234

typedef struct __mavlink_gdpilot_status_request_t
{
 uint8_t module_id; ///< Module ID
} mavlink_gdpilot_status_request_t;

#define MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN 1
#define MAVLINK_MSG_ID_234_LEN 1

#define MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_CRC 138
#define MAVLINK_MSG_ID_234_CRC 138



#define MAVLINK_MESSAGE_INFO_GDPILOT_STATUS_REQUEST { \
	"GDPILOT_STATUS_REQUEST", \
	1, \
	{  { "module_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_gdpilot_status_request_t, module_id) }, \
         } \
}


/**
 * @brief Pack a gdpilot_status_request message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param module_id Module ID
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gdpilot_status_request_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t module_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN];
	_mav_put_uint8_t(buf, 0, module_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN);
#else
	mavlink_gdpilot_status_request_t packet;
	packet.module_id = module_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN);
#endif
}

/**
 * @brief Pack a gdpilot_status_request message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param module_id Module ID
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gdpilot_status_request_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t module_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN];
	_mav_put_uint8_t(buf, 0, module_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN);
#else
	mavlink_gdpilot_status_request_t packet;
	packet.module_id = module_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN);
#endif
}

/**
 * @brief Encode a gdpilot_status_request struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gdpilot_status_request C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gdpilot_status_request_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gdpilot_status_request_t* gdpilot_status_request)
{
	return mavlink_msg_gdpilot_status_request_pack(system_id, component_id, msg, gdpilot_status_request->module_id);
}

/**
 * @brief Encode a gdpilot_status_request struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gdpilot_status_request C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gdpilot_status_request_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_gdpilot_status_request_t* gdpilot_status_request)
{
	return mavlink_msg_gdpilot_status_request_pack_chan(system_id, component_id, chan, msg, gdpilot_status_request->module_id);
}

/**
 * @brief Send a gdpilot_status_request message
 * @param chan MAVLink channel to send the message
 *
 * @param module_id Module ID
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gdpilot_status_request_send(mavlink_channel_t chan, uint8_t module_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN];
	_mav_put_uint8_t(buf, 0, module_id);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST, buf, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST, buf, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN);
#endif
#else
	mavlink_gdpilot_status_request_t packet;
	packet.module_id = module_id;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST, (const char *)&packet, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST, (const char *)&packet, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_gdpilot_status_request_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t module_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint8_t(buf, 0, module_id);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST, buf, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST, buf, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN);
#endif
#else
	mavlink_gdpilot_status_request_t *packet = (mavlink_gdpilot_status_request_t *)msgbuf;
	packet->module_id = module_id;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST, (const char *)packet, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST, (const char *)packet, MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE GDPILOT_STATUS_REQUEST UNPACKING


/**
 * @brief Get field module_id from gdpilot_status_request message
 *
 * @return Module ID
 */
static inline uint8_t mavlink_msg_gdpilot_status_request_get_module_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Decode a gdpilot_status_request message into a struct
 *
 * @param msg The message to decode
 * @param gdpilot_status_request C-struct to decode the message contents into
 */
static inline void mavlink_msg_gdpilot_status_request_decode(const mavlink_message_t* msg, mavlink_gdpilot_status_request_t* gdpilot_status_request)
{
#if MAVLINK_NEED_BYTE_SWAP
	gdpilot_status_request->module_id = mavlink_msg_gdpilot_status_request_get_module_id(msg);
#else
	memcpy(gdpilot_status_request, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_GDPILOT_STATUS_REQUEST_LEN);
#endif
}
