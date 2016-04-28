// MESSAGE GLOBAL_POSITION_NEITZKE PACKING

#define MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE 225

typedef struct __mavlink_global_position_neitzke_t
{
 uint32_t time_boot_ms; /*< Timestamp (milliseconds since system boot)*/
 int32_t lat; /*< Latitude, expressed as * 1E7*/
 int32_t lon; /*< Longitude, expressed as * 1E7*/
 int32_t alt; /*< Altitude in meters, expressed as * 1000 (millimeters), AMSL (not WGS84 - note that virtually all GPS modules provide the AMSL as well)*/
 int32_t relative_alt; /*< Altitude above ground in meters, expressed as * 1000 (millimeters)*/
 int32_t baro_alt; /*< Altitude above ground in meters, expressed in cm*/
 int16_t vx; /*< Ground X Speed (Latitude), expressed as m/s * 100*/
 int16_t vy; /*< Ground Y Speed (Longitude), expressed as m/s * 100*/
 int16_t vz; /*< Ground Z Speed (Altitude), expressed as m/s * 100*/
 uint16_t hdg; /*< Compass heading in degrees * 100, 0.0..359.99 degrees. If unknown, set to: UINT16_MAX*/
} mavlink_global_position_neitzke_t;

#define MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN 32
#define MAVLINK_MSG_ID_225_LEN 32

#define MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_CRC 249
#define MAVLINK_MSG_ID_225_CRC 249



#define MAVLINK_MESSAGE_INFO_GLOBAL_POSITION_NEITZKE { \
	"GLOBAL_POSITION_NEITZKE", \
	10, \
	{  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_global_position_neitzke_t, time_boot_ms) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_global_position_neitzke_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_global_position_neitzke_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_global_position_neitzke_t, alt) }, \
         { "relative_alt", NULL, MAVLINK_TYPE_INT32_T, 0, 16, offsetof(mavlink_global_position_neitzke_t, relative_alt) }, \
         { "baro_alt", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_global_position_neitzke_t, baro_alt) }, \
         { "vx", NULL, MAVLINK_TYPE_INT16_T, 0, 24, offsetof(mavlink_global_position_neitzke_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_INT16_T, 0, 26, offsetof(mavlink_global_position_neitzke_t, vy) }, \
         { "vz", NULL, MAVLINK_TYPE_INT16_T, 0, 28, offsetof(mavlink_global_position_neitzke_t, vz) }, \
         { "hdg", NULL, MAVLINK_TYPE_UINT16_T, 0, 30, offsetof(mavlink_global_position_neitzke_t, hdg) }, \
         } \
}


/**
 * @brief Pack a global_position_neitzke message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms Timestamp (milliseconds since system boot)
 * @param lat Latitude, expressed as * 1E7
 * @param lon Longitude, expressed as * 1E7
 * @param alt Altitude in meters, expressed as * 1000 (millimeters), AMSL (not WGS84 - note that virtually all GPS modules provide the AMSL as well)
 * @param relative_alt Altitude above ground in meters, expressed as * 1000 (millimeters)
 * @param baro_alt Altitude above ground in meters, expressed in cm
 * @param vx Ground X Speed (Latitude), expressed as m/s * 100
 * @param vy Ground Y Speed (Longitude), expressed as m/s * 100
 * @param vz Ground Z Speed (Altitude), expressed as m/s * 100
 * @param hdg Compass heading in degrees * 100, 0.0..359.99 degrees. If unknown, set to: UINT16_MAX
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_global_position_neitzke_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint32_t time_boot_ms, int32_t lat, int32_t lon, int32_t alt, int32_t relative_alt, int32_t baro_alt, int16_t vx, int16_t vy, int16_t vz, uint16_t hdg)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN];
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_int32_t(buf, 4, lat);
	_mav_put_int32_t(buf, 8, lon);
	_mav_put_int32_t(buf, 12, alt);
	_mav_put_int32_t(buf, 16, relative_alt);
	_mav_put_int32_t(buf, 20, baro_alt);
	_mav_put_int16_t(buf, 24, vx);
	_mav_put_int16_t(buf, 26, vy);
	_mav_put_int16_t(buf, 28, vz);
	_mav_put_uint16_t(buf, 30, hdg);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN);
#else
	mavlink_global_position_neitzke_t packet;
	packet.time_boot_ms = time_boot_ms;
	packet.lat = lat;
	packet.lon = lon;
	packet.alt = alt;
	packet.relative_alt = relative_alt;
	packet.baro_alt = baro_alt;
	packet.vx = vx;
	packet.vy = vy;
	packet.vz = vz;
	packet.hdg = hdg;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN);
#endif
}

/**
 * @brief Pack a global_position_neitzke message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_boot_ms Timestamp (milliseconds since system boot)
 * @param lat Latitude, expressed as * 1E7
 * @param lon Longitude, expressed as * 1E7
 * @param alt Altitude in meters, expressed as * 1000 (millimeters), AMSL (not WGS84 - note that virtually all GPS modules provide the AMSL as well)
 * @param relative_alt Altitude above ground in meters, expressed as * 1000 (millimeters)
 * @param baro_alt Altitude above ground in meters, expressed in cm
 * @param vx Ground X Speed (Latitude), expressed as m/s * 100
 * @param vy Ground Y Speed (Longitude), expressed as m/s * 100
 * @param vz Ground Z Speed (Altitude), expressed as m/s * 100
 * @param hdg Compass heading in degrees * 100, 0.0..359.99 degrees. If unknown, set to: UINT16_MAX
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_global_position_neitzke_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint32_t time_boot_ms,int32_t lat,int32_t lon,int32_t alt,int32_t relative_alt,int32_t baro_alt,int16_t vx,int16_t vy,int16_t vz,uint16_t hdg)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN];
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_int32_t(buf, 4, lat);
	_mav_put_int32_t(buf, 8, lon);
	_mav_put_int32_t(buf, 12, alt);
	_mav_put_int32_t(buf, 16, relative_alt);
	_mav_put_int32_t(buf, 20, baro_alt);
	_mav_put_int16_t(buf, 24, vx);
	_mav_put_int16_t(buf, 26, vy);
	_mav_put_int16_t(buf, 28, vz);
	_mav_put_uint16_t(buf, 30, hdg);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN);
#else
	mavlink_global_position_neitzke_t packet;
	packet.time_boot_ms = time_boot_ms;
	packet.lat = lat;
	packet.lon = lon;
	packet.alt = alt;
	packet.relative_alt = relative_alt;
	packet.baro_alt = baro_alt;
	packet.vx = vx;
	packet.vy = vy;
	packet.vz = vz;
	packet.hdg = hdg;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN);
#endif
}

/**
 * @brief Encode a global_position_neitzke struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param global_position_neitzke C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_global_position_neitzke_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_global_position_neitzke_t* global_position_neitzke)
{
	return mavlink_msg_global_position_neitzke_pack(system_id, component_id, msg, global_position_neitzke->time_boot_ms, global_position_neitzke->lat, global_position_neitzke->lon, global_position_neitzke->alt, global_position_neitzke->relative_alt, global_position_neitzke->baro_alt, global_position_neitzke->vx, global_position_neitzke->vy, global_position_neitzke->vz, global_position_neitzke->hdg);
}

/**
 * @brief Encode a global_position_neitzke struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param global_position_neitzke C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_global_position_neitzke_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_global_position_neitzke_t* global_position_neitzke)
{
	return mavlink_msg_global_position_neitzke_pack_chan(system_id, component_id, chan, msg, global_position_neitzke->time_boot_ms, global_position_neitzke->lat, global_position_neitzke->lon, global_position_neitzke->alt, global_position_neitzke->relative_alt, global_position_neitzke->baro_alt, global_position_neitzke->vx, global_position_neitzke->vy, global_position_neitzke->vz, global_position_neitzke->hdg);
}

/**
 * @brief Send a global_position_neitzke message
 * @param chan MAVLink channel to send the message
 *
 * @param time_boot_ms Timestamp (milliseconds since system boot)
 * @param lat Latitude, expressed as * 1E7
 * @param lon Longitude, expressed as * 1E7
 * @param alt Altitude in meters, expressed as * 1000 (millimeters), AMSL (not WGS84 - note that virtually all GPS modules provide the AMSL as well)
 * @param relative_alt Altitude above ground in meters, expressed as * 1000 (millimeters)
 * @param baro_alt Altitude above ground in meters, expressed in cm
 * @param vx Ground X Speed (Latitude), expressed as m/s * 100
 * @param vy Ground Y Speed (Longitude), expressed as m/s * 100
 * @param vz Ground Z Speed (Altitude), expressed as m/s * 100
 * @param hdg Compass heading in degrees * 100, 0.0..359.99 degrees. If unknown, set to: UINT16_MAX
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_global_position_neitzke_send(mavlink_channel_t chan, uint32_t time_boot_ms, int32_t lat, int32_t lon, int32_t alt, int32_t relative_alt, int32_t baro_alt, int16_t vx, int16_t vy, int16_t vz, uint16_t hdg)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN];
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_int32_t(buf, 4, lat);
	_mav_put_int32_t(buf, 8, lon);
	_mav_put_int32_t(buf, 12, alt);
	_mav_put_int32_t(buf, 16, relative_alt);
	_mav_put_int32_t(buf, 20, baro_alt);
	_mav_put_int16_t(buf, 24, vx);
	_mav_put_int16_t(buf, 26, vy);
	_mav_put_int16_t(buf, 28, vz);
	_mav_put_uint16_t(buf, 30, hdg);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE, buf, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE, buf, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN);
#endif
#else
	mavlink_global_position_neitzke_t packet;
	packet.time_boot_ms = time_boot_ms;
	packet.lat = lat;
	packet.lon = lon;
	packet.alt = alt;
	packet.relative_alt = relative_alt;
	packet.baro_alt = baro_alt;
	packet.vx = vx;
	packet.vy = vy;
	packet.vz = vz;
	packet.hdg = hdg;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE, (const char *)&packet, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE, (const char *)&packet, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_global_position_neitzke_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t time_boot_ms, int32_t lat, int32_t lon, int32_t alt, int32_t relative_alt, int32_t baro_alt, int16_t vx, int16_t vy, int16_t vz, uint16_t hdg)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_int32_t(buf, 4, lat);
	_mav_put_int32_t(buf, 8, lon);
	_mav_put_int32_t(buf, 12, alt);
	_mav_put_int32_t(buf, 16, relative_alt);
	_mav_put_int32_t(buf, 20, baro_alt);
	_mav_put_int16_t(buf, 24, vx);
	_mav_put_int16_t(buf, 26, vy);
	_mav_put_int16_t(buf, 28, vz);
	_mav_put_uint16_t(buf, 30, hdg);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE, buf, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE, buf, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN);
#endif
#else
	mavlink_global_position_neitzke_t *packet = (mavlink_global_position_neitzke_t *)msgbuf;
	packet->time_boot_ms = time_boot_ms;
	packet->lat = lat;
	packet->lon = lon;
	packet->alt = alt;
	packet->relative_alt = relative_alt;
	packet->baro_alt = baro_alt;
	packet->vx = vx;
	packet->vy = vy;
	packet->vz = vz;
	packet->hdg = hdg;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE, (const char *)packet, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE, (const char *)packet, MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE GLOBAL_POSITION_NEITZKE UNPACKING


/**
 * @brief Get field time_boot_ms from global_position_neitzke message
 *
 * @return Timestamp (milliseconds since system boot)
 */
static inline uint32_t mavlink_msg_global_position_neitzke_get_time_boot_ms(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field lat from global_position_neitzke message
 *
 * @return Latitude, expressed as * 1E7
 */
static inline int32_t mavlink_msg_global_position_neitzke_get_lat(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field lon from global_position_neitzke message
 *
 * @return Longitude, expressed as * 1E7
 */
static inline int32_t mavlink_msg_global_position_neitzke_get_lon(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Get field alt from global_position_neitzke message
 *
 * @return Altitude in meters, expressed as * 1000 (millimeters), AMSL (not WGS84 - note that virtually all GPS modules provide the AMSL as well)
 */
static inline int32_t mavlink_msg_global_position_neitzke_get_alt(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  12);
}

/**
 * @brief Get field relative_alt from global_position_neitzke message
 *
 * @return Altitude above ground in meters, expressed as * 1000 (millimeters)
 */
static inline int32_t mavlink_msg_global_position_neitzke_get_relative_alt(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  16);
}

/**
 * @brief Get field baro_alt from global_position_neitzke message
 *
 * @return Altitude above ground in meters, expressed in cm
 */
static inline int32_t mavlink_msg_global_position_neitzke_get_baro_alt(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  20);
}

/**
 * @brief Get field vx from global_position_neitzke message
 *
 * @return Ground X Speed (Latitude), expressed as m/s * 100
 */
static inline int16_t mavlink_msg_global_position_neitzke_get_vx(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  24);
}

/**
 * @brief Get field vy from global_position_neitzke message
 *
 * @return Ground Y Speed (Longitude), expressed as m/s * 100
 */
static inline int16_t mavlink_msg_global_position_neitzke_get_vy(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  26);
}

/**
 * @brief Get field vz from global_position_neitzke message
 *
 * @return Ground Z Speed (Altitude), expressed as m/s * 100
 */
static inline int16_t mavlink_msg_global_position_neitzke_get_vz(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  28);
}

/**
 * @brief Get field hdg from global_position_neitzke message
 *
 * @return Compass heading in degrees * 100, 0.0..359.99 degrees. If unknown, set to: UINT16_MAX
 */
static inline uint16_t mavlink_msg_global_position_neitzke_get_hdg(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  30);
}

/**
 * @brief Decode a global_position_neitzke message into a struct
 *
 * @param msg The message to decode
 * @param global_position_neitzke C-struct to decode the message contents into
 */
static inline void mavlink_msg_global_position_neitzke_decode(const mavlink_message_t* msg, mavlink_global_position_neitzke_t* global_position_neitzke)
{
#if MAVLINK_NEED_BYTE_SWAP
	global_position_neitzke->time_boot_ms = mavlink_msg_global_position_neitzke_get_time_boot_ms(msg);
	global_position_neitzke->lat = mavlink_msg_global_position_neitzke_get_lat(msg);
	global_position_neitzke->lon = mavlink_msg_global_position_neitzke_get_lon(msg);
	global_position_neitzke->alt = mavlink_msg_global_position_neitzke_get_alt(msg);
	global_position_neitzke->relative_alt = mavlink_msg_global_position_neitzke_get_relative_alt(msg);
	global_position_neitzke->baro_alt = mavlink_msg_global_position_neitzke_get_baro_alt(msg);
	global_position_neitzke->vx = mavlink_msg_global_position_neitzke_get_vx(msg);
	global_position_neitzke->vy = mavlink_msg_global_position_neitzke_get_vy(msg);
	global_position_neitzke->vz = mavlink_msg_global_position_neitzke_get_vz(msg);
	global_position_neitzke->hdg = mavlink_msg_global_position_neitzke_get_hdg(msg);
#else
	memcpy(global_position_neitzke, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_GLOBAL_POSITION_NEITZKE_LEN);
#endif
}
