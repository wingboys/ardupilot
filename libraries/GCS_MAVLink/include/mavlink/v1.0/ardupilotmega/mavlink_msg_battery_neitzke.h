// MESSAGE BATTERY_NEITZKE PACKING

#define MAVLINK_MSG_ID_BATTERY_NEITZKE 235

typedef struct __mavlink_battery_neitzke_t
{
 float currentB; ///< Battery Current (A)
 float voltageB; ///< Battery Voltage (V)
 float voltagePH; ///< Board Voltage (V)
} mavlink_battery_neitzke_t;

#define MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN 12
#define MAVLINK_MSG_ID_235_LEN 12

#define MAVLINK_MSG_ID_BATTERY_NEITZKE_CRC 105
#define MAVLINK_MSG_ID_235_CRC 105



#define MAVLINK_MESSAGE_INFO_BATTERY_NEITZKE { \
	"BATTERY_NEITZKE", \
	3, \
	{  { "currentB", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_battery_neitzke_t, currentB) }, \
         { "voltageB", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_battery_neitzke_t, voltageB) }, \
         { "voltagePH", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_battery_neitzke_t, voltagePH) }, \
         } \
}


/**
 * @brief Pack a battery_neitzke message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param currentB Battery Current (A)
 * @param voltageB Battery Voltage (V)
 * @param voltagePH Board Voltage (V)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_battery_neitzke_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       float currentB, float voltageB, float voltagePH)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN];
	_mav_put_float(buf, 0, currentB);
	_mav_put_float(buf, 4, voltageB);
	_mav_put_float(buf, 8, voltagePH);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN);
#else
	mavlink_battery_neitzke_t packet;
	packet.currentB = currentB;
	packet.voltageB = voltageB;
	packet.voltagePH = voltagePH;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_BATTERY_NEITZKE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN, MAVLINK_MSG_ID_BATTERY_NEITZKE_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN);
#endif
}

/**
 * @brief Pack a battery_neitzke message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param currentB Battery Current (A)
 * @param voltageB Battery Voltage (V)
 * @param voltagePH Board Voltage (V)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_battery_neitzke_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           float currentB,float voltageB,float voltagePH)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN];
	_mav_put_float(buf, 0, currentB);
	_mav_put_float(buf, 4, voltageB);
	_mav_put_float(buf, 8, voltagePH);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN);
#else
	mavlink_battery_neitzke_t packet;
	packet.currentB = currentB;
	packet.voltageB = voltageB;
	packet.voltagePH = voltagePH;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_BATTERY_NEITZKE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN, MAVLINK_MSG_ID_BATTERY_NEITZKE_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN);
#endif
}

/**
 * @brief Encode a battery_neitzke struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param battery_neitzke C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_battery_neitzke_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_battery_neitzke_t* battery_neitzke)
{
	return mavlink_msg_battery_neitzke_pack(system_id, component_id, msg, battery_neitzke->currentB, battery_neitzke->voltageB, battery_neitzke->voltagePH);
}

/**
 * @brief Encode a battery_neitzke struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param battery_neitzke C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_battery_neitzke_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_battery_neitzke_t* battery_neitzke)
{
	return mavlink_msg_battery_neitzke_pack_chan(system_id, component_id, chan, msg, battery_neitzke->currentB, battery_neitzke->voltageB, battery_neitzke->voltagePH);
}

/**
 * @brief Send a battery_neitzke message
 * @param chan MAVLink channel to send the message
 *
 * @param currentB Battery Current (A)
 * @param voltageB Battery Voltage (V)
 * @param voltagePH Board Voltage (V)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_battery_neitzke_send(mavlink_channel_t chan, float currentB, float voltageB, float voltagePH)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN];
	_mav_put_float(buf, 0, currentB);
	_mav_put_float(buf, 4, voltageB);
	_mav_put_float(buf, 8, voltagePH);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_NEITZKE, buf, MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN, MAVLINK_MSG_ID_BATTERY_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_NEITZKE, buf, MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN);
#endif
#else
	mavlink_battery_neitzke_t packet;
	packet.currentB = currentB;
	packet.voltageB = voltageB;
	packet.voltagePH = voltagePH;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_NEITZKE, (const char *)&packet, MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN, MAVLINK_MSG_ID_BATTERY_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_NEITZKE, (const char *)&packet, MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_battery_neitzke_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float currentB, float voltageB, float voltagePH)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_float(buf, 0, currentB);
	_mav_put_float(buf, 4, voltageB);
	_mav_put_float(buf, 8, voltagePH);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_NEITZKE, buf, MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN, MAVLINK_MSG_ID_BATTERY_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_NEITZKE, buf, MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN);
#endif
#else
	mavlink_battery_neitzke_t *packet = (mavlink_battery_neitzke_t *)msgbuf;
	packet->currentB = currentB;
	packet->voltageB = voltageB;
	packet->voltagePH = voltagePH;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_NEITZKE, (const char *)packet, MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN, MAVLINK_MSG_ID_BATTERY_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_NEITZKE, (const char *)packet, MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE BATTERY_NEITZKE UNPACKING


/**
 * @brief Get field currentB from battery_neitzke message
 *
 * @return Battery Current (A)
 */
static inline float mavlink_msg_battery_neitzke_get_currentB(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field voltageB from battery_neitzke message
 *
 * @return Battery Voltage (V)
 */
static inline float mavlink_msg_battery_neitzke_get_voltageB(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field voltagePH from battery_neitzke message
 *
 * @return Board Voltage (V)
 */
static inline float mavlink_msg_battery_neitzke_get_voltagePH(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a battery_neitzke message into a struct
 *
 * @param msg The message to decode
 * @param battery_neitzke C-struct to decode the message contents into
 */
static inline void mavlink_msg_battery_neitzke_decode(const mavlink_message_t* msg, mavlink_battery_neitzke_t* battery_neitzke)
{
#if MAVLINK_NEED_BYTE_SWAP
	battery_neitzke->currentB = mavlink_msg_battery_neitzke_get_currentB(msg);
	battery_neitzke->voltageB = mavlink_msg_battery_neitzke_get_voltageB(msg);
	battery_neitzke->voltagePH = mavlink_msg_battery_neitzke_get_voltagePH(msg);
#else
	memcpy(battery_neitzke, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_BATTERY_NEITZKE_LEN);
#endif
}
