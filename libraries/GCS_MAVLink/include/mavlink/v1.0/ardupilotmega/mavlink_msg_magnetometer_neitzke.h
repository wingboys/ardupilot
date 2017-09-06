// MESSAGE MAGNETOMETER_NEITZKE PACKING

#define MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE 237

typedef struct __mavlink_magnetometer_neitzke_t
{
 float x; ///< x component magnetic field
 float y; ///< y component magnetic field
 float z; ///< z component magnetic field
} mavlink_magnetometer_neitzke_t;

#define MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN 12
#define MAVLINK_MSG_ID_237_LEN 12

#define MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_CRC 87
#define MAVLINK_MSG_ID_237_CRC 87



#define MAVLINK_MESSAGE_INFO_MAGNETOMETER_NEITZKE { \
	"MAGNETOMETER_NEITZKE", \
	3, \
	{  { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_magnetometer_neitzke_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_magnetometer_neitzke_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_magnetometer_neitzke_t, z) }, \
         } \
}


/**
 * @brief Pack a magnetometer_neitzke message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param x x component magnetic field
 * @param y y component magnetic field
 * @param z z component magnetic field
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_magnetometer_neitzke_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN];
	_mav_put_float(buf, 0, x);
	_mav_put_float(buf, 4, y);
	_mav_put_float(buf, 8, z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN);
#else
	mavlink_magnetometer_neitzke_t packet;
	packet.x = x;
	packet.y = y;
	packet.z = z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN);
#endif
}

/**
 * @brief Pack a magnetometer_neitzke message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param x x component magnetic field
 * @param y y component magnetic field
 * @param z z component magnetic field
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_magnetometer_neitzke_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           float x,float y,float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN];
	_mav_put_float(buf, 0, x);
	_mav_put_float(buf, 4, y);
	_mav_put_float(buf, 8, z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN);
#else
	mavlink_magnetometer_neitzke_t packet;
	packet.x = x;
	packet.y = y;
	packet.z = z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN);
#endif
}

/**
 * @brief Encode a magnetometer_neitzke struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param magnetometer_neitzke C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_magnetometer_neitzke_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_magnetometer_neitzke_t* magnetometer_neitzke)
{
	return mavlink_msg_magnetometer_neitzke_pack(system_id, component_id, msg, magnetometer_neitzke->x, magnetometer_neitzke->y, magnetometer_neitzke->z);
}

/**
 * @brief Encode a magnetometer_neitzke struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param magnetometer_neitzke C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_magnetometer_neitzke_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_magnetometer_neitzke_t* magnetometer_neitzke)
{
	return mavlink_msg_magnetometer_neitzke_pack_chan(system_id, component_id, chan, msg, magnetometer_neitzke->x, magnetometer_neitzke->y, magnetometer_neitzke->z);
}

/**
 * @brief Send a magnetometer_neitzke message
 * @param chan MAVLink channel to send the message
 *
 * @param x x component magnetic field
 * @param y y component magnetic field
 * @param z z component magnetic field
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_magnetometer_neitzke_send(mavlink_channel_t chan, float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN];
	_mav_put_float(buf, 0, x);
	_mav_put_float(buf, 4, y);
	_mav_put_float(buf, 8, z);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE, buf, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE, buf, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN);
#endif
#else
	mavlink_magnetometer_neitzke_t packet;
	packet.x = x;
	packet.y = y;
	packet.z = z;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE, (const char *)&packet, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE, (const char *)&packet, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_magnetometer_neitzke_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_float(buf, 0, x);
	_mav_put_float(buf, 4, y);
	_mav_put_float(buf, 8, z);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE, buf, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE, buf, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN);
#endif
#else
	mavlink_magnetometer_neitzke_t *packet = (mavlink_magnetometer_neitzke_t *)msgbuf;
	packet->x = x;
	packet->y = y;
	packet->z = z;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE, (const char *)packet, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE, (const char *)packet, MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE MAGNETOMETER_NEITZKE UNPACKING


/**
 * @brief Get field x from magnetometer_neitzke message
 *
 * @return x component magnetic field
 */
static inline float mavlink_msg_magnetometer_neitzke_get_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field y from magnetometer_neitzke message
 *
 * @return y component magnetic field
 */
static inline float mavlink_msg_magnetometer_neitzke_get_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field z from magnetometer_neitzke message
 *
 * @return z component magnetic field
 */
static inline float mavlink_msg_magnetometer_neitzke_get_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a magnetometer_neitzke message into a struct
 *
 * @param msg The message to decode
 * @param magnetometer_neitzke C-struct to decode the message contents into
 */
static inline void mavlink_msg_magnetometer_neitzke_decode(const mavlink_message_t* msg, mavlink_magnetometer_neitzke_t* magnetometer_neitzke)
{
#if MAVLINK_NEED_BYTE_SWAP
	magnetometer_neitzke->x = mavlink_msg_magnetometer_neitzke_get_x(msg);
	magnetometer_neitzke->y = mavlink_msg_magnetometer_neitzke_get_y(msg);
	magnetometer_neitzke->z = mavlink_msg_magnetometer_neitzke_get_z(msg);
#else
	memcpy(magnetometer_neitzke, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_MAGNETOMETER_NEITZKE_LEN);
#endif
}
