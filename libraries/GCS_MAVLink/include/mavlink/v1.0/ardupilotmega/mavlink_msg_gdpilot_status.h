// MESSAGE GDPILOT_STATUS PACKING

#define MAVLINK_MSG_ID_GDPILOT_STATUS 234

typedef struct __mavlink_gdpilot_status_t
{
 uint8_t module_id; ///< Module ID
 uint8_t value; ///< Status
} mavlink_gdpilot_status_t;

#define MAVLINK_MSG_ID_GDPILOT_STATUS_LEN 2
#define MAVLINK_MSG_ID_234_LEN 2

#define MAVLINK_MSG_ID_GDPILOT_STATUS_CRC 58
#define MAVLINK_MSG_ID_234_CRC 58



#define MAVLINK_MESSAGE_INFO_GDPILOT_STATUS { \
	"GDPILOT_STATUS", \
	2, \
	{  { "module_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_gdpilot_status_t, module_id) }, \
         { "value", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_gdpilot_status_t, value) }, \
         } \
}


/**
 * @brief Pack a gdpilot_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param module_id Module ID
 * @param value Status
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gdpilot_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t module_id, uint8_t value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GDPILOT_STATUS_LEN];
	_mav_put_uint8_t(buf, 0, module_id);
	_mav_put_uint8_t(buf, 1, value);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GDPILOT_STATUS_LEN);
#else
	mavlink_gdpilot_status_t packet;
	packet.module_id = module_id;
	packet.value = value;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GDPILOT_STATUS_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_GDPILOT_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GDPILOT_STATUS_LEN, MAVLINK_MSG_ID_GDPILOT_STATUS_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GDPILOT_STATUS_LEN);
#endif
}

/**
 * @brief Pack a gdpilot_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param module_id Module ID
 * @param value Status
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gdpilot_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t module_id,uint8_t value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GDPILOT_STATUS_LEN];
	_mav_put_uint8_t(buf, 0, module_id);
	_mav_put_uint8_t(buf, 1, value);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GDPILOT_STATUS_LEN);
#else
	mavlink_gdpilot_status_t packet;
	packet.module_id = module_id;
	packet.value = value;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GDPILOT_STATUS_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_GDPILOT_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GDPILOT_STATUS_LEN, MAVLINK_MSG_ID_GDPILOT_STATUS_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GDPILOT_STATUS_LEN);
#endif
}

/**
 * @brief Encode a gdpilot_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gdpilot_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gdpilot_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gdpilot_status_t* gdpilot_status)
{
	return mavlink_msg_gdpilot_status_pack(system_id, component_id, msg, gdpilot_status->module_id, gdpilot_status->value);
}

/**
 * @brief Encode a gdpilot_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gdpilot_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gdpilot_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_gdpilot_status_t* gdpilot_status)
{
	return mavlink_msg_gdpilot_status_pack_chan(system_id, component_id, chan, msg, gdpilot_status->module_id, gdpilot_status->value);
}

/**
 * @brief Send a gdpilot_status message
 * @param chan MAVLink channel to send the message
 *
 * @param module_id Module ID
 * @param value Status
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gdpilot_status_send(mavlink_channel_t chan, uint8_t module_id, uint8_t value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GDPILOT_STATUS_LEN];
	_mav_put_uint8_t(buf, 0, module_id);
	_mav_put_uint8_t(buf, 1, value);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GDPILOT_STATUS, buf, MAVLINK_MSG_ID_GDPILOT_STATUS_LEN, MAVLINK_MSG_ID_GDPILOT_STATUS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GDPILOT_STATUS, buf, MAVLINK_MSG_ID_GDPILOT_STATUS_LEN);
#endif
#else
	mavlink_gdpilot_status_t packet;
	packet.module_id = module_id;
	packet.value = value;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GDPILOT_STATUS, (const char *)&packet, MAVLINK_MSG_ID_GDPILOT_STATUS_LEN, MAVLINK_MSG_ID_GDPILOT_STATUS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GDPILOT_STATUS, (const char *)&packet, MAVLINK_MSG_ID_GDPILOT_STATUS_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_GDPILOT_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_gdpilot_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t module_id, uint8_t value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint8_t(buf, 0, module_id);
	_mav_put_uint8_t(buf, 1, value);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GDPILOT_STATUS, buf, MAVLINK_MSG_ID_GDPILOT_STATUS_LEN, MAVLINK_MSG_ID_GDPILOT_STATUS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GDPILOT_STATUS, buf, MAVLINK_MSG_ID_GDPILOT_STATUS_LEN);
#endif
#else
	mavlink_gdpilot_status_t *packet = (mavlink_gdpilot_status_t *)msgbuf;
	packet->module_id = module_id;
	packet->value = value;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GDPILOT_STATUS, (const char *)packet, MAVLINK_MSG_ID_GDPILOT_STATUS_LEN, MAVLINK_MSG_ID_GDPILOT_STATUS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GDPILOT_STATUS, (const char *)packet, MAVLINK_MSG_ID_GDPILOT_STATUS_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE GDPILOT_STATUS UNPACKING


/**
 * @brief Get field module_id from gdpilot_status message
 *
 * @return Module ID
 */
static inline uint8_t mavlink_msg_gdpilot_status_get_module_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field value from gdpilot_status message
 *
 * @return Status
 */
static inline uint8_t mavlink_msg_gdpilot_status_get_value(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Decode a gdpilot_status message into a struct
 *
 * @param msg The message to decode
 * @param gdpilot_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_gdpilot_status_decode(const mavlink_message_t* msg, mavlink_gdpilot_status_t* gdpilot_status)
{
#if MAVLINK_NEED_BYTE_SWAP
	gdpilot_status->module_id = mavlink_msg_gdpilot_status_get_module_id(msg);
	gdpilot_status->value = mavlink_msg_gdpilot_status_get_value(msg);
#else
	memcpy(gdpilot_status, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_GDPILOT_STATUS_LEN);
#endif
}
