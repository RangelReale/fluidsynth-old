/* FluidSynth - A Software Synthesizer
 *
 * Copyright (C) 2003  Peter Hanappe and others.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License
 * as published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *  
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA
 */

#ifndef _FLUIDSYNTH_MIDI_H
#define _FLUIDSYNTH_MIDI_H

#ifdef __cplusplus
extern "C" {
#endif

enum fluid_midi_event_type {
  /* channel messages */
  NOTE_OFF = 0x80,
  NOTE_ON = 0x90,
  KEY_PRESSURE = 0xa0,
  CONTROL_CHANGE = 0xb0,
  PROGRAM_CHANGE = 0xc0,
  CHANNEL_PRESSURE = 0xd0,
  PITCH_BEND = 0xe0,
  /* system exclusive */
  MIDI_SYSEX = 0xf0,
  /* system common - never in midi files */
  MIDI_TIME_CODE = 0xf1,
  MIDI_SONG_POSITION = 0xf2,
  MIDI_SONG_SELECT = 0xf3,
  MIDI_TUNE_REQUEST = 0xf6,
  MIDI_EOX = 0xf7,
  /* system real-time - never in midi files */
  MIDI_SYNC = 0xf8,
  MIDI_TICK = 0xf9,
  MIDI_START = 0xfa,
  MIDI_CONTINUE = 0xfb,
  MIDI_STOP = 0xfc,
  MIDI_ACTIVE_SENSING = 0xfe,
  MIDI_SYSTEM_RESET = 0xff,
  /* meta event - for midi files only */
  MIDI_META_EVENT = 0xff
};

enum fluid_midi_control_change {
  BANK_SELECT_MSB = 0x00,
  MODULATION_MSB = 0x01,
  BREATH_MSB = 0x02,
  FOOT_MSB = 0x04,
  PORTAMENTO_TIME_MSB = 0x05,
  DATA_ENTRY_MSB = 0x06,
  VOLUME_MSB = 0x07,
  BALANCE_MSB = 0x08,
  PAN_MSB = 0x0A,
  EXPRESSION_MSB = 0x0B,
  EFFECTS1_MSB = 0x0C,
  EFFECTS2_MSB = 0x0D,
  GPC1_MSB = 0x10, /* general purpose controller */
  GPC2_MSB = 0x11,
  GPC3_MSB = 0x12,
  GPC4_MSB = 0x13,
  BANK_SELECT_LSB = 0x20,
  MODULATION_WHEEL_LSB = 0x21,
  BREATH_LSB = 0x22,
  FOOT_LSB = 0x24,
  PORTAMENTO_TIME_LSB = 0x25,
  DATA_ENTRY_LSB = 0x26,
  VOLUME_LSB = 0x27,
  BALANCE_LSB = 0x28,
  PAN_LSB = 0x2A,
  EXPRESSION_LSB = 0x2B,
  EFFECTS1_LSB = 0x2C,
  EFFECTS2_LSB = 0x2D,
  GPC1_LSB = 0x30,
  GPC2_LSB = 0x31,
  GPC3_LSB = 0x32,
  GPC4_LSB = 0x33,
  SUSTAIN_SWITCH = 0x40,
  PORTAMENTO_SWITCH = 0x41,
  SOSTENUTO_SWITCH = 0x42,
  SOFT_PEDAL_SWITCH = 0x43,
  LEGATO_SWITCH = 0x45,
  HOLD2_SWITCH = 0x45,
  SOUND_CTRL1 = 0x46,
  SOUND_CTRL2 = 0x47,
  SOUND_CTRL3 = 0x48,
  SOUND_CTRL4 = 0x49,
  SOUND_CTRL5 = 0x4A,
  SOUND_CTRL6 = 0x4B,
  SOUND_CTRL7 = 0x4C,
  SOUND_CTRL8 = 0x4D,
  SOUND_CTRL9 = 0x4E,
  SOUND_CTRL10 = 0x4F,
  GPC5 = 0x50,
  GPC6 = 0x51,
  GPC7 = 0x52,
  GPC8 = 0x53,
  PORTAMENTO_CTRL = 0x54,
  EFFECTS_DEPTH1 = 0x5B,
  EFFECTS_DEPTH2 = 0x5C,
  EFFECTS_DEPTH3 = 0x5D,
  EFFECTS_DEPTH4 = 0x5E,
  EFFECTS_DEPTH5 = 0x5F,
  DATA_ENTRY_INCR = 0x60,
  DATA_ENTRY_DECR = 0x61,
  NRPN_LSB = 0x62,
  NRPN_MSB = 0x63,
  RPN_LSB = 0x64,
  RPN_MSB = 0x65,
  ALL_SOUND_OFF = 0x78,
  ALL_CTRL_OFF = 0x79,
  LOCAL_CONTROL = 0x7A,
  ALL_NOTES_OFF = 0x7B,
  OMNI_OFF = 0x7C,
  OMNI_ON = 0x7D,
  POLY_OFF = 0x7E,
  POLY_ON = 0x7F
};

/* General MIDI RPN event numbers (LSB, MSB = 0) */
enum midi_rpn_event {
  RPN_PITCH_BEND_RANGE = 0x00,
  RPN_CHANNEL_FINE_TUNE = 0x01,
  RPN_CHANNEL_COARSE_TUNE = 0x02,
  RPN_TUNING_PROGRAM_CHANGE = 0x03,
  RPN_TUNING_BANK_SELECT = 0x04,
  RPN_MODULATION_DEPTH_RANGE = 0x05
};

enum midi_meta_event {
  MIDI_TEXT = 0x01,
  MIDI_COPYRIGHT = 0x02,
  MIDI_TRACK_NAME = 0x03,
  MIDI_INST_NAME = 0x04,
  MIDI_LYRIC = 0x05,
  MIDI_MARKER = 0x06,
  MIDI_CUE_POINT = 0x07,
  MIDI_EOT = 0x2f,
  MIDI_SET_TEMPO = 0x51,
  MIDI_SMPTE_OFFSET = 0x54,
  MIDI_TIME_SIGNATURE = 0x58,
  MIDI_KEY_SIGNATURE = 0x59,
  MIDI_SEQUENCER_EVENT = 0x7f
};

/* MIDI SYSEX useful manufacturer values */
enum midi_sysex_manuf {
  MIDI_SYSEX_MANUF_ROLAND       = 0x41,         /**< Roland manufacturer ID */
  MIDI_SYSEX_UNIV_NON_REALTIME  = 0x7E,         /**< Universal non realtime message */
  MIDI_SYSEX_UNIV_REALTIME      = 0x7F          /**< Universal realtime message */
};

#define MIDI_SYSEX_DEVICE_ID_ALL        0x7F    /**< Device ID used in SYSEX messages to indicate all devices */

/* SYSEX sub-ID #1 which follows device ID */
#define MIDI_SYSEX_MIDI_TUNING_ID       0x08    /**< Sysex sub-ID #1 for MIDI tuning messages */
#define MIDI_SYSEX_GM_ID                0x09    /**< Sysex sub-ID #1 for General MIDI messages */

/**
 * SYSEX tuning message IDs.
 */
enum midi_sysex_tuning_msg_id {
  MIDI_SYSEX_TUNING_BULK_DUMP_REQ       = 0x00, /**< Bulk tuning dump request (non-realtime) */
  MIDI_SYSEX_TUNING_BULK_DUMP           = 0x01, /**< Bulk tuning dump response (non-realtime) */
  MIDI_SYSEX_TUNING_NOTE_TUNE           = 0x02, /**< Tuning note change message (realtime) */
  MIDI_SYSEX_TUNING_BULK_DUMP_REQ_BANK  = 0x03, /**< Bulk tuning dump request (with bank, non-realtime) */
  MIDI_SYSEX_TUNING_BULK_DUMP_BANK      = 0x04, /**< Bulk tuning dump resonse (with bank, non-realtime) */
  MIDI_SYSEX_TUNING_OCTAVE_DUMP_1BYTE   = 0x05, /**< Octave tuning dump using 1 byte values (non-realtime) */
  MIDI_SYSEX_TUNING_OCTAVE_DUMP_2BYTE   = 0x06, /**< Octave tuning dump using 2 byte values (non-realtime) */ 
  MIDI_SYSEX_TUNING_NOTE_TUNE_BANK      = 0x07, /**< Tuning note change message (with bank, realtime/non-realtime) */
  MIDI_SYSEX_TUNING_OCTAVE_TUNE_1BYTE   = 0x08, /**< Octave tuning message using 1 byte values (realtime/non-realtime) */
  MIDI_SYSEX_TUNING_OCTAVE_TUNE_2BYTE   = 0x09  /**< Octave tuning message using 2 byte values (realtime/non-realtime) */
};

/* General MIDI sub-ID #2 */
#define MIDI_SYSEX_GM_ON                0x01    /**< Enable GM mode */
#define MIDI_SYSEX_GM_OFF               0x02    /**< Disable GM mode */

enum fluid_driver_status
{
  FLUID_MIDI_READY,
  FLUID_MIDI_LISTENING,
  FLUID_MIDI_DONE
};

/**
 * @file midi.h
 * @brief Functions for MIDI events, drivers and MIDI file playback.
 */

FLUIDSYNTH_API fluid_midi_event_t* new_fluid_midi_event(void);
FLUIDSYNTH_API int delete_fluid_midi_event(fluid_midi_event_t* event);

FLUIDSYNTH_API int fluid_midi_event_set_type(fluid_midi_event_t* evt, int type);
FLUIDSYNTH_API int fluid_midi_event_get_type(fluid_midi_event_t* evt);
FLUIDSYNTH_API int fluid_midi_event_set_channel(fluid_midi_event_t* evt, int chan);
FLUIDSYNTH_API int fluid_midi_event_get_channel(fluid_midi_event_t* evt);
FLUIDSYNTH_API int fluid_midi_event_set_dtime(fluid_midi_event_t* evt, unsigned int dtime);
FLUIDSYNTH_API unsigned int fluid_midi_event_get_dtime(fluid_midi_event_t* evt);
FLUIDSYNTH_API int fluid_midi_event_get_key(fluid_midi_event_t* evt);
FLUIDSYNTH_API int fluid_midi_event_set_key(fluid_midi_event_t* evt, int key);
FLUIDSYNTH_API int fluid_midi_event_get_velocity(fluid_midi_event_t* evt);
FLUIDSYNTH_API int fluid_midi_event_set_velocity(fluid_midi_event_t* evt, int vel);
FLUIDSYNTH_API int fluid_midi_event_get_control(fluid_midi_event_t* evt);
FLUIDSYNTH_API int fluid_midi_event_set_control(fluid_midi_event_t* evt, int ctrl);
FLUIDSYNTH_API int fluid_midi_event_get_value(fluid_midi_event_t* evt);
FLUIDSYNTH_API int fluid_midi_event_set_value(fluid_midi_event_t* evt, int val);
FLUIDSYNTH_API int fluid_midi_event_get_program(fluid_midi_event_t* evt);
FLUIDSYNTH_API int fluid_midi_event_set_program(fluid_midi_event_t* evt, int val);
FLUIDSYNTH_API int fluid_midi_event_get_pitch(fluid_midi_event_t* evt);
FLUIDSYNTH_API int fluid_midi_event_set_pitch(fluid_midi_event_t* evt, int val);
FLUIDSYNTH_API int fluid_midi_event_set_sysex(fluid_midi_event_t* evt, void *data,
                                              int size, int dynamic);
FLUIDSYNTH_API char *fluid_midi_event_get_text(fluid_midi_event_t* evt);
FLUIDSYNTH_API int fluid_midi_event_get_text_length(fluid_midi_event_t* evt);


FLUIDSYNTH_API unsigned int fluid_midi_timed_event_get_ticks(fluid_midi_timed_event_t* evt);
FLUIDSYNTH_API fluid_player_t* fluid_midi_timed_event_get_player(fluid_midi_timed_event_t* evt);
FLUIDSYNTH_API fluid_track_t* fluid_midi_timed_event_get_track(fluid_midi_timed_event_t* evt);
FLUIDSYNTH_API fluid_midi_event_t* fluid_midi_timed_event_get_event(fluid_midi_timed_event_t* evt);

/**
 * MIDI track type.
 * @since 1.1.0
 */

FLUIDSYNTH_API fluid_track_t* new_fluid_track(int num);
FLUIDSYNTH_API int delete_fluid_track(fluid_track_t* track);
FLUIDSYNTH_API int fluid_track_get_num(fluid_track_t* track);
FLUIDSYNTH_API int fluid_track_set_name(fluid_track_t* track, char* name);
FLUIDSYNTH_API char* fluid_track_get_name(fluid_track_t* track);
FLUIDSYNTH_API int fluid_track_add_event(fluid_track_t* track, fluid_midi_event_t* evt);
FLUIDSYNTH_API fluid_midi_event_t* fluid_track_first_event(fluid_track_t* track);
FLUIDSYNTH_API fluid_midi_event_t* fluid_track_next_event(fluid_track_t* track);
FLUIDSYNTH_API int fluid_track_get_duration(fluid_track_t* track);
FLUIDSYNTH_API int fluid_track_reset(fluid_track_t* track);


/**
 * MIDI router rule type.
 * @since 1.1.0
 */
typedef enum
{
  FLUID_MIDI_ROUTER_RULE_NOTE,                  /**< MIDI note rule */
  FLUID_MIDI_ROUTER_RULE_CC,                    /**< MIDI controller rule */
  FLUID_MIDI_ROUTER_RULE_PROG_CHANGE,           /**< MIDI program change rule */
  FLUID_MIDI_ROUTER_RULE_PITCH_BEND,            /**< MIDI pitch bend rule */
  FLUID_MIDI_ROUTER_RULE_CHANNEL_PRESSURE,      /**< MIDI channel pressure rule */
  FLUID_MIDI_ROUTER_RULE_KEY_PRESSURE,          /**< MIDI key pressure rule */
  FLUID_MIDI_ROUTER_RULE_COUNT                  /**< Total count of rule types */
} fluid_midi_router_rule_type;

/**
 * Generic callback function for MIDI events.
 * @param data User defined data pointer
 * @param event The MIDI event
 * @return Should return #FLUID_OK on success, #FLUID_FAILED otherwise
 *
 * Will be used between
 * - MIDI driver and MIDI router
 * - MIDI router and synth
 * to communicate events.
 * In the not-so-far future...
 */
typedef int (*handle_onload_func_t)(void* data, fluid_player_t* player);

typedef int(*handle_tick_func_t)(void* data, fluid_player_t* player, unsigned int ticks);

typedef int (*handle_midi_event_func_t)(void* data, fluid_midi_event_t* event);

typedef int(*handle_midi_timed_event_func_t)(void* data, fluid_midi_timed_event_t* event);

FLUIDSYNTH_API fluid_midi_router_t* new_fluid_midi_router(fluid_settings_t* settings,
						       handle_midi_event_func_t handler, 
						       void* event_handler_data); 
FLUIDSYNTH_API int delete_fluid_midi_router(fluid_midi_router_t* handler); 
FLUIDSYNTH_API int fluid_midi_router_set_default_rules (fluid_midi_router_t *router);
FLUIDSYNTH_API int fluid_midi_router_clear_rules (fluid_midi_router_t *router);
FLUIDSYNTH_API int fluid_midi_router_add_rule (fluid_midi_router_t *router,
                                               fluid_midi_router_rule_t *rule, int type);
FLUIDSYNTH_API fluid_midi_router_rule_t *new_fluid_midi_router_rule (void);
FLUIDSYNTH_API void delete_fluid_midi_router_rule (fluid_midi_router_rule_t *rule);
FLUIDSYNTH_API void fluid_midi_router_rule_set_chan (fluid_midi_router_rule_t *rule,
                                                     int min, int max, float mul, int add);
FLUIDSYNTH_API void fluid_midi_router_rule_set_param1 (fluid_midi_router_rule_t *rule,
                                                       int min, int max, float mul, int add);
FLUIDSYNTH_API void fluid_midi_router_rule_set_param2 (fluid_midi_router_rule_t *rule,
                                                       int min, int max, float mul, int add);
FLUIDSYNTH_API int fluid_midi_router_handle_midi_event(void* data, fluid_midi_event_t* event);
FLUIDSYNTH_API int fluid_midi_dump_prerouter(void* data, fluid_midi_event_t* event); 
FLUIDSYNTH_API int fluid_midi_dump_postrouter(void* data, fluid_midi_event_t* event); 


FLUIDSYNTH_API 
fluid_midi_driver_t* new_fluid_midi_driver(fluid_settings_t* settings, 
					 handle_midi_event_func_t handler, 
					 void* event_handler_data);

FLUIDSYNTH_API void delete_fluid_midi_driver(fluid_midi_driver_t* driver);


/**
 * MIDI player status enum.
 * @since 1.1.0
 */
enum fluid_player_status
{
  FLUID_PLAYER_READY,           /**< Player is ready */
  FLUID_PLAYER_PLAYING,         /**< Player is currently playing */
  FLUID_PLAYER_DONE             /**< Player is finished playing */
};

FLUIDSYNTH_API fluid_player_t* new_fluid_player(fluid_synth_t* synth);
FLUIDSYNTH_API int delete_fluid_player(fluid_player_t* player);
FLUIDSYNTH_API int fluid_player_add(fluid_player_t* player, const char *midifile);
FLUIDSYNTH_API int fluid_player_add_mem(fluid_player_t* player, const void *buffer, size_t len);
FLUIDSYNTH_API int fluid_player_play(fluid_player_t* player);
FLUIDSYNTH_API int fluid_player_stop(fluid_player_t* player);
FLUIDSYNTH_API int fluid_player_join(fluid_player_t* player);
FLUIDSYNTH_API int fluid_player_set_loop(fluid_player_t* player, int loop);
FLUIDSYNTH_API int fluid_player_set_midi_tempo(fluid_player_t* player, int tempo);
FLUIDSYNTH_API int fluid_player_set_bpm(fluid_player_t* player, int bpm);
FLUIDSYNTH_API int fluid_player_get_status(fluid_player_t* player);
FLUIDSYNTH_API int fluid_player_count_tracks(fluid_player_t* player);
FLUIDSYNTH_API fluid_track_t* fluid_player_get_track(fluid_player_t* player, int i);
FLUIDSYNTH_API int fluid_player_set_playback_callback(fluid_player_t* player, handle_midi_event_func_t handler, void* handler_data);
FLUIDSYNTH_API int fluid_player_set_timed_playback_callback(fluid_player_t* player, handle_midi_timed_event_func_t handler, void* handler_data);
FLUIDSYNTH_API int fluid_player_set_onload_callback(fluid_player_t* player, handle_onload_func_t handler, void* handler_data);
FLUIDSYNTH_API int fluid_player_set_tick_callback(fluid_player_t* player, int tick_interval, handle_tick_func_t handler, void* handler_data);
FLUIDSYNTH_API fluid_synth_t* fluid_player_get_synth(fluid_player_t* player);

#ifdef __cplusplus
}
#endif

#endif /* _FLUIDSYNTH_MIDI_H */
