// MESSAGE AMBIENT_NEITZKE PACKING

#define MAVLINK_MSG_ID_AMBIENT_NEITZKE 236

typedef struct __mavlink_ambient_neitzke_t
{
 float temperature; ///< Ambient Temperature (C)
 float pressure; ///< Barometric Pressure (kPa)
} mavlink_ambient_neitzke_t;

#define MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN 8
#define MAVLINK_MSG_ID_236_LEN 8

#define MAVLINK_MSG_ID_AMBIENT_NEITZKE_CRC 111
#define MAVLINK_MSG_ID_236_CRC 111



#define MAVLINK_MESSAGE_INFO_AMBIENT_NEITZKE { \
	"AMBIENT_NEITZKE", \
	2, \
	{  { "temperature", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_ambient_neitzke_t, temperature) }, \
         { "pressure", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_ambient_neitzke_t, pressure) }, \
         } \
}


/**
 * @brief Pack a ambient_neitzke message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param temperature Ambient Temperature (C)
 * @param pressure Barometric Pressure (kPa)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_ambient_neitzke_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       float temperature, float pressure)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN];
	_mav_put_float(buf, 0, temperature);
	_mav_put_float(buf, 4, pressure);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN);
#else
	mavlink_ambient_neitzke_t packet;
	packet.temperature = temperature;
	packet.pressure = pressure;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_AMBIENT_NEITZKE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN, MAVLINK_MSG_ID_AMBIENT_NEITZKE_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN);
#endif
}

/**
 * @brief Pack a ambient_neitzke message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param temperature Ambient Temperature (C)
 * @param pressure Barometric Pressure (kPa)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_ambient_neitzke_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           float temperature,float pressure)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN];
	_mav_put_float(buf, 0, temperature);
	_mav_put_float(buf, 4, pressure);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN);
#else
	mavlink_ambient_neitzke_t packet;
	packet.temperature = temperature;
	packet.pressure = pressure;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_AMBIENT_NEITZKE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN, MAVLINK_MSG_ID_AMBIENT_NEITZKE_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN);
#endif
}

/**
 * @brief Encode a ambient_neitzke struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param ambient_neitzke C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_ambient_neitzke_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_ambient_neitzke_t* ambient_neitzke)
{
	return mavlink_msg_ambient_neitzke_pack(system_id, component_id, msg, ambient_neitzke->temperature, ambient_neitzke->pressure);
}

/**
 * @brief Encode a ambient_neitzke struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param ambient_neitzke C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_ambient_neitzke_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_ambient_neitzke_t* ambient_neitzke)
{
	return mavlink_msg_ambient_neitzke_pack_chan(system_id, component_id, chan, msg, ambient_neitzke->temperature, ambient_neitzke->pressure);
}

/**
 * @brief Send a ambient_neitzke message
 * @param chan MAVLink channel to send the message
 *
 * @param temperature Ambient Temperature (C)
 * @param pressure Barometric Pressure (kPa)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_ambient_neitzke_send(mavlink_channel_t chan, float temperature, float pressure)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN];
	_mav_put_float(buf, 0, temperature);
	_mav_put_float(buf, 4, pressure);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AMBIENT_NEITZKE, buf, MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN, MAVLINK_MSG_ID_AMBIENT_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AMBIENT_NEITZKE, buf, MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN);
#endif
#else
	mavlink_ambient_neitzke_t packet;
	packet.temperature = temperature;
	packet.pressure = pressure;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AMBIENT_NEITZKE, (const char *)&packet, MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN, MAVLINK_MSG_ID_AMBIENT_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AMBIENT_NEITZKE, (const char *)&packet, MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_ambient_neitzke_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float temperature, float pressure)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_float(buf, 0, temperature);
	_mav_put_float(buf, 4, pressure);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AMBIENT_NEITZKE, buf, MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN, MAVLINK_MSG_ID_AMBIENT_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AMBIENT_NEITZKE, buf, MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN);
#endif
#else
	mavlink_ambient_neitzke_t *packet = (mavlink_ambient_neitzke_t *)msgbuf;
	packet->temperature = temperature;
	packet->pressure = pressure;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AMBIENT_NEITZKE, (const char *)packet, MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN, MAVLINK_MSG_ID_AMBIENT_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AMBIENT_NEITZKE, (const char *)packet, MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE AMBIENT_NEITZKE UNPACKING


/**
 * @brief Get field temperature from ambient_neitzke message
 *
 * @return Ambient Temperature (C)
 */
static inline float mavlink_msg_ambient_neitzke_get_temperature(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field pressure from ambient_neitzke message
 *
 * @return Barometric Pressure (kPa)
 */
static inline float mavlink_msg_ambient_neitzke_get_pressure(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Decode a ambient_neitzke message into a struct
 *
 * @param msg The message to decode
 * @param ambient_neitzke C-struct to decode the message contents into
 */
static inline void mavlink_msg_ambient_neitzke_decode(const mavlink_message_t* msg, mavlink_ambient_neitzke_t* ambient_neitzke)
{
#if MAVLINK_NEED_BYTE_SWAP
	ambient_neitzke->temperature = mavlink_msg_ambient_neitzke_get_temperature(msg);
	ambient_neitzke->pressure = mavlink_msg_ambient_neitzke_get_pressure(msg);
#else
	memcpy(ambient_neitzke, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_AMBIENT_NEITZKE_LEN);
#endif
}
