// MESSAGE LOCAL_POSITION_NEITZKE PACKING

#define MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE 225

typedef struct __mavlink_local_position_neitzke_t
{
 uint32_t time_boot_ms; /*< Timestamp (milliseconds since system boot)*/
 int32_t x; /*< current x position relative to the home location in cm*/
 int32_t y; /*< current y position relative to the home location in cm*/
 int32_t z; /*< current z position relative to the home location in cm*/
 int32_t baro_alt; /*< Baro altitude above ground in meters, expressed in cm*/
 int16_t vx; /*< Fused velocity in North direction in NEU frame in cm/s*/
 int16_t vy; /*< Fused velocity in East direction in NEU frame in cm/s*/
 int16_t vz; /*< Fused velocity in Up direction in NEU frame in cm/s*/
 uint16_t hdg; /*< Compass heading in degrees * 100, 0.0..359.99 degrees. If unknown, set to: UINT16_MAX*/
} mavlink_local_position_neitzke_t;

#define MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN 28
#define MAVLINK_MSG_ID_225_LEN 28

#define MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_CRC 62
#define MAVLINK_MSG_ID_225_CRC 62



#define MAVLINK_MESSAGE_INFO_LOCAL_POSITION_NEITZKE { \
	"LOCAL_POSITION_NEITZKE", \
	9, \
	{  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_local_position_neitzke_t, time_boot_ms) }, \
         { "x", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_local_position_neitzke_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_local_position_neitzke_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_local_position_neitzke_t, z) }, \
         { "baro_alt", NULL, MAVLINK_TYPE_INT32_T, 0, 16, offsetof(mavlink_local_position_neitzke_t, baro_alt) }, \
         { "vx", NULL, MAVLINK_TYPE_INT16_T, 0, 20, offsetof(mavlink_local_position_neitzke_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_INT16_T, 0, 22, offsetof(mavlink_local_position_neitzke_t, vy) }, \
         { "vz", NULL, MAVLINK_TYPE_INT16_T, 0, 24, offsetof(mavlink_local_position_neitzke_t, vz) }, \
         { "hdg", NULL, MAVLINK_TYPE_UINT16_T, 0, 26, offsetof(mavlink_local_position_neitzke_t, hdg) }, \
         } \
}


/**
 * @brief Pack a local_position_neitzke message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms Timestamp (milliseconds since system boot)
 * @param x current x position relative to the home location in cm
 * @param y current y position relative to the home location in cm
 * @param z current z position relative to the home location in cm
 * @param baro_alt Baro altitude above ground in meters, expressed in cm
 * @param vx Fused velocity in North direction in NEU frame in cm/s
 * @param vy Fused velocity in East direction in NEU frame in cm/s
 * @param vz Fused velocity in Up direction in NEU frame in cm/s
 * @param hdg Compass heading in degrees * 100, 0.0..359.99 degrees. If unknown, set to: UINT16_MAX
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_local_position_neitzke_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint32_t time_boot_ms, int32_t x, int32_t y, int32_t z, int32_t baro_alt, int16_t vx, int16_t vy, int16_t vz, uint16_t hdg)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN];
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_int32_t(buf, 4, x);
	_mav_put_int32_t(buf, 8, y);
	_mav_put_int32_t(buf, 12, z);
	_mav_put_int32_t(buf, 16, baro_alt);
	_mav_put_int16_t(buf, 20, vx);
	_mav_put_int16_t(buf, 22, vy);
	_mav_put_int16_t(buf, 24, vz);
	_mav_put_uint16_t(buf, 26, hdg);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN);
#else
	mavlink_local_position_neitzke_t packet;
	packet.time_boot_ms = time_boot_ms;
	packet.x = x;
	packet.y = y;
	packet.z = z;
	packet.baro_alt = baro_alt;
	packet.vx = vx;
	packet.vy = vy;
	packet.vz = vz;
	packet.hdg = hdg;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN);
#endif
}

/**
 * @brief Pack a local_position_neitzke message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_boot_ms Timestamp (milliseconds since system boot)
 * @param x current x position relative to the home location in cm
 * @param y current y position relative to the home location in cm
 * @param z current z position relative to the home location in cm
 * @param baro_alt Baro altitude above ground in meters, expressed in cm
 * @param vx Fused velocity in North direction in NEU frame in cm/s
 * @param vy Fused velocity in East direction in NEU frame in cm/s
 * @param vz Fused velocity in Up direction in NEU frame in cm/s
 * @param hdg Compass heading in degrees * 100, 0.0..359.99 degrees. If unknown, set to: UINT16_MAX
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_local_position_neitzke_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint32_t time_boot_ms,int32_t x,int32_t y,int32_t z,int32_t baro_alt,int16_t vx,int16_t vy,int16_t vz,uint16_t hdg)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN];
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_int32_t(buf, 4, x);
	_mav_put_int32_t(buf, 8, y);
	_mav_put_int32_t(buf, 12, z);
	_mav_put_int32_t(buf, 16, baro_alt);
	_mav_put_int16_t(buf, 20, vx);
	_mav_put_int16_t(buf, 22, vy);
	_mav_put_int16_t(buf, 24, vz);
	_mav_put_uint16_t(buf, 26, hdg);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN);
#else
	mavlink_local_position_neitzke_t packet;
	packet.time_boot_ms = time_boot_ms;
	packet.x = x;
	packet.y = y;
	packet.z = z;
	packet.baro_alt = baro_alt;
	packet.vx = vx;
	packet.vy = vy;
	packet.vz = vz;
	packet.hdg = hdg;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN);
#endif
}

/**
 * @brief Encode a local_position_neitzke struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param local_position_neitzke C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_local_position_neitzke_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_local_position_neitzke_t* local_position_neitzke)
{
	return mavlink_msg_local_position_neitzke_pack(system_id, component_id, msg, local_position_neitzke->time_boot_ms, local_position_neitzke->x, local_position_neitzke->y, local_position_neitzke->z, local_position_neitzke->baro_alt, local_position_neitzke->vx, local_position_neitzke->vy, local_position_neitzke->vz, local_position_neitzke->hdg);
}

/**
 * @brief Encode a local_position_neitzke struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param local_position_neitzke C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_local_position_neitzke_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_local_position_neitzke_t* local_position_neitzke)
{
	return mavlink_msg_local_position_neitzke_pack_chan(system_id, component_id, chan, msg, local_position_neitzke->time_boot_ms, local_position_neitzke->x, local_position_neitzke->y, local_position_neitzke->z, local_position_neitzke->baro_alt, local_position_neitzke->vx, local_position_neitzke->vy, local_position_neitzke->vz, local_position_neitzke->hdg);
}

/**
 * @brief Send a local_position_neitzke message
 * @param chan MAVLink channel to send the message
 *
 * @param time_boot_ms Timestamp (milliseconds since system boot)
 * @param x current x position relative to the home location in cm
 * @param y current y position relative to the home location in cm
 * @param z current z position relative to the home location in cm
 * @param baro_alt Baro altitude above ground in meters, expressed in cm
 * @param vx Fused velocity in North direction in NEU frame in cm/s
 * @param vy Fused velocity in East direction in NEU frame in cm/s
 * @param vz Fused velocity in Up direction in NEU frame in cm/s
 * @param hdg Compass heading in degrees * 100, 0.0..359.99 degrees. If unknown, set to: UINT16_MAX
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_local_position_neitzke_send(mavlink_channel_t chan, uint32_t time_boot_ms, int32_t x, int32_t y, int32_t z, int32_t baro_alt, int16_t vx, int16_t vy, int16_t vz, uint16_t hdg)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN];
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_int32_t(buf, 4, x);
	_mav_put_int32_t(buf, 8, y);
	_mav_put_int32_t(buf, 12, z);
	_mav_put_int32_t(buf, 16, baro_alt);
	_mav_put_int16_t(buf, 20, vx);
	_mav_put_int16_t(buf, 22, vy);
	_mav_put_int16_t(buf, 24, vz);
	_mav_put_uint16_t(buf, 26, hdg);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE, buf, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE, buf, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN);
#endif
#else
	mavlink_local_position_neitzke_t packet;
	packet.time_boot_ms = time_boot_ms;
	packet.x = x;
	packet.y = y;
	packet.z = z;
	packet.baro_alt = baro_alt;
	packet.vx = vx;
	packet.vy = vy;
	packet.vz = vz;
	packet.hdg = hdg;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE, (const char *)&packet, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE, (const char *)&packet, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_local_position_neitzke_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t time_boot_ms, int32_t x, int32_t y, int32_t z, int32_t baro_alt, int16_t vx, int16_t vy, int16_t vz, uint16_t hdg)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_int32_t(buf, 4, x);
	_mav_put_int32_t(buf, 8, y);
	_mav_put_int32_t(buf, 12, z);
	_mav_put_int32_t(buf, 16, baro_alt);
	_mav_put_int16_t(buf, 20, vx);
	_mav_put_int16_t(buf, 22, vy);
	_mav_put_int16_t(buf, 24, vz);
	_mav_put_uint16_t(buf, 26, hdg);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE, buf, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE, buf, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN);
#endif
#else
	mavlink_local_position_neitzke_t *packet = (mavlink_local_position_neitzke_t *)msgbuf;
	packet->time_boot_ms = time_boot_ms;
	packet->x = x;
	packet->y = y;
	packet->z = z;
	packet->baro_alt = baro_alt;
	packet->vx = vx;
	packet->vy = vy;
	packet->vz = vz;
	packet->hdg = hdg;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE, (const char *)packet, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE, (const char *)packet, MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE LOCAL_POSITION_NEITZKE UNPACKING


/**
 * @brief Get field time_boot_ms from local_position_neitzke message
 *
 * @return Timestamp (milliseconds since system boot)
 */
static inline uint32_t mavlink_msg_local_position_neitzke_get_time_boot_ms(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field x from local_position_neitzke message
 *
 * @return current x position relative to the home location in cm
 */
static inline int32_t mavlink_msg_local_position_neitzke_get_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field y from local_position_neitzke message
 *
 * @return current y position relative to the home location in cm
 */
static inline int32_t mavlink_msg_local_position_neitzke_get_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Get field z from local_position_neitzke message
 *
 * @return current z position relative to the home location in cm
 */
static inline int32_t mavlink_msg_local_position_neitzke_get_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  12);
}

/**
 * @brief Get field baro_alt from local_position_neitzke message
 *
 * @return Baro altitude above ground in meters, expressed in cm
 */
static inline int32_t mavlink_msg_local_position_neitzke_get_baro_alt(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  16);
}

/**
 * @brief Get field vx from local_position_neitzke message
 *
 * @return Fused velocity in North direction in NEU frame in cm/s
 */
static inline int16_t mavlink_msg_local_position_neitzke_get_vx(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  20);
}

/**
 * @brief Get field vy from local_position_neitzke message
 *
 * @return Fused velocity in East direction in NEU frame in cm/s
 */
static inline int16_t mavlink_msg_local_position_neitzke_get_vy(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  22);
}

/**
 * @brief Get field vz from local_position_neitzke message
 *
 * @return Fused velocity in Up direction in NEU frame in cm/s
 */
static inline int16_t mavlink_msg_local_position_neitzke_get_vz(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  24);
}

/**
 * @brief Get field hdg from local_position_neitzke message
 *
 * @return Compass heading in degrees * 100, 0.0..359.99 degrees. If unknown, set to: UINT16_MAX
 */
static inline uint16_t mavlink_msg_local_position_neitzke_get_hdg(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  26);
}

/**
 * @brief Decode a local_position_neitzke message into a struct
 *
 * @param msg The message to decode
 * @param local_position_neitzke C-struct to decode the message contents into
 */
static inline void mavlink_msg_local_position_neitzke_decode(const mavlink_message_t* msg, mavlink_local_position_neitzke_t* local_position_neitzke)
{
#if MAVLINK_NEED_BYTE_SWAP
	local_position_neitzke->time_boot_ms = mavlink_msg_local_position_neitzke_get_time_boot_ms(msg);
	local_position_neitzke->x = mavlink_msg_local_position_neitzke_get_x(msg);
	local_position_neitzke->y = mavlink_msg_local_position_neitzke_get_y(msg);
	local_position_neitzke->z = mavlink_msg_local_position_neitzke_get_z(msg);
	local_position_neitzke->baro_alt = mavlink_msg_local_position_neitzke_get_baro_alt(msg);
	local_position_neitzke->vx = mavlink_msg_local_position_neitzke_get_vx(msg);
	local_position_neitzke->vy = mavlink_msg_local_position_neitzke_get_vy(msg);
	local_position_neitzke->vz = mavlink_msg_local_position_neitzke_get_vz(msg);
	local_position_neitzke->hdg = mavlink_msg_local_position_neitzke_get_hdg(msg);
#else
	memcpy(local_position_neitzke, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_LOCAL_POSITION_NEITZKE_LEN);
#endif
}
