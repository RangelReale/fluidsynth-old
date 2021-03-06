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

#ifndef _FLUID_MIDI_H
#define _FLUID_MIDI_H

#include "fluidsynth_priv.h"
#include "fluid_sys.h"
#include "fluid_list.h"

typedef struct _fluid_midi_parser_t fluid_midi_parser_t;

fluid_midi_parser_t* new_fluid_midi_parser(void);
int delete_fluid_midi_parser(fluid_midi_parser_t* parser);
fluid_midi_event_t* fluid_midi_parser_parse(fluid_midi_parser_t* parser, unsigned char c);


/***************************************************************
 *
 *                   CONSTANTS & ENUM
 */


#define MAX_NUMBER_OF_TRACKS 128


/***************************************************************
 *
 *         TYPE DEFINITIONS & FUNCTION DECLARATIONS
 */

/* From ctype.h */
#define fluid_isascii(c)    (((c) & ~0x7f) == 0)



/*
 * fluid_midi_event_t
 */
struct _fluid_midi_event_t {
  fluid_midi_event_t* next; /* Link to next event */
  void *paramptr;           /* Pointer parameter (for SYSEX data), size is stored to param1, param2 indicates if pointer should be freed (dynamic if TRUE) */
  unsigned int dtime;       /* Delay (ticks) between this and previous event. midi tracks. */
  unsigned int param1;      /* First parameter */
  unsigned int param2;      /* Second parameter */
  unsigned char type;       /* MIDI event type */
  unsigned char channel;    /* MIDI channel */
};

/*
* fluid_midi_timed_event_t
*/
struct _fluid_midi_timed_event_t {
	unsigned int ticks;
	fluid_player_t *player;
	fluid_track_t *track;
	fluid_midi_event_t* event; /* Link to the event */
};


/*
 * fluid_track_t
 */
struct _fluid_track_t {
  char* name;
  int num;
  fluid_midi_event_t *first;
  fluid_midi_event_t *cur;
  fluid_midi_event_t *last;
  unsigned int ticks;
};

typedef struct _fluid_track_t fluid_track_t;

int fluid_track_send_events(fluid_track_t* track,
			   fluid_synth_t* synth,
			   fluid_player_t* player,
			   unsigned int ticks);

#define fluid_track_eot(track)  ((track)->cur == NULL)


/**
 * fluid_playlist_item
 * Used as the `data' elements of the fluid_player.playlist.
 * Represents either a filename or a pre-loaded memory buffer.
 * Exactly one of `filename' and `buffer' is non-NULL.
 */
typedef struct
{
    char* filename;     /** Name of file (owned); NULL if data pre-loaded */
    void* buffer;       /** The MIDI file data (owned); NULL if filename */
    size_t buffer_len;  /** Number of bytes in buffer; 0 if filename */
} fluid_playlist_item;

/*
 * fluid_player
 */
struct _fluid_player_t {
  int status;
  int ntracks;
  fluid_track_t *track[MAX_NUMBER_OF_TRACKS];
  fluid_synth_t* synth;
  fluid_timer_t* system_timer;
  fluid_sample_timer_t* sample_timer;

  int loop; /* -1 = loop infinitely, otherwise times left to loop the playlist */
  fluid_list_t* playlist; /* List of fluid_playlist_item* objects */
  fluid_list_t* currentfile; /* points to an item in files, or NULL if not playing */

  char send_program_change; /* should we ignore the program changes? */
  char use_system_timer;   /* if zero, use sample timers, otherwise use system clock timer */
  char reset_synth_between_songs; /* 1 if system reset should be sent to the synth between songs. */
  int start_ticks;          /* the number of tempo ticks passed at the last tempo change */
  int cur_ticks;            /* the number of tempo ticks passed */
  int begin_msec;           /* the time (msec) of the beginning of the file */
  int start_msec;           /* the start time of the last tempo change */
  int cur_msec;             /* the current time */
  int miditempo;            /* as indicated by MIDI SetTempo: n 24th of a usec per midi-clock. bravo! */
  double deltatime;         /* milliseconds per midi tick. depends on set-tempo */
  unsigned int division;

  handle_midi_event_func_t playback_callback; /* function fired on each midi event as it is played */
  void* playback_userdata; /* pointer to user-defined data passed to playback_callback function */

  handle_midi_timed_event_func_t timedplayback_callback; /* function fired on each timed midi event as it is played */
  void* timedplayback_userdata; /* pointer to user-defined timed data passed to timedplayback_callback function */

  handle_onload_func_t onload_callback; /* function fired when new MIDI data is loaded, such as a new file */
  void* onload_userdata; /* pointer to user-defined data passed to onload_callback function */

  int tick_interval;
  int tick_interval_last;
  handle_tick_func_t tick_callback; /* function fired on a new tick */
  void* tick_userdata; /* pointer to user-defined data passed to tick_callback function */
};

int fluid_player_add_track(fluid_player_t* player, fluid_track_t* track);
int fluid_player_callback(void* data, unsigned int msec);
int fluid_player_reset(fluid_player_t* player);
int fluid_player_load(fluid_player_t* player, fluid_playlist_item *item);

void fluid_player_settings(fluid_settings_t* settings);


/*
 * fluid_midi_file
 */
typedef struct {
  const char* buffer;           /* Entire contents of MIDI file (borrowed) */
  int buf_len;                  /* Length of buffer, in bytes */
  int buf_pos;                  /* Current read position in contents buffer */
  int eof;                      /* The "end of file" condition */
  int running_status;
  int c;
  int type;
  int ntracks;
  int uses_smpte;
  unsigned int smpte_fps;
  unsigned int smpte_res;
  unsigned int division;       /* If uses_SMPTE == 0 then division is
				  ticks per beat (quarter-note) */
  double tempo;                /* Beats per second (SI rules =) */
  int tracklen;
  int trackpos;
  int eot;
  int varlen;
  int dtime;
} fluid_midi_file;

fluid_midi_file* new_fluid_midi_file(const char* buffer, size_t length);
void delete_fluid_midi_file(fluid_midi_file* mf);
int fluid_midi_file_read_mthd(fluid_midi_file* midifile);
int fluid_midi_file_load_tracks(fluid_midi_file* midifile, fluid_player_t* player);
int fluid_midi_file_read_track(fluid_midi_file* mf, fluid_player_t* player, int num);
int fluid_midi_file_read_event(fluid_midi_file* mf, fluid_track_t* track);
int fluid_midi_file_read_varlen(fluid_midi_file* mf);
int fluid_midi_file_getc(fluid_midi_file* mf);
int fluid_midi_file_push(fluid_midi_file* mf, int c);
int fluid_midi_file_read(fluid_midi_file* mf, void* buf, int len);
int fluid_midi_file_skip(fluid_midi_file* mf, int len);
int fluid_midi_file_eof(fluid_midi_file* mf);
int fluid_midi_file_read_tracklen(fluid_midi_file* mf);
int fluid_midi_file_eot(fluid_midi_file* mf);
int fluid_midi_file_get_division(fluid_midi_file* midifile);


#define FLUID_MIDI_PARSER_MAX_DATA_SIZE 1024    /**< Maximum size of MIDI parameters/data (largest is SYSEX data) */

/*
 * fluid_midi_parser_t
 */
struct _fluid_midi_parser_t {
  unsigned char status;           /* Identifies the type of event, that is currently received ('Noteon', 'Pitch Bend' etc). */
  unsigned char channel;          /* The channel of the event that is received (in case of a channel event) */
  unsigned int nr_bytes;          /* How many bytes have been read for the current event? */
  unsigned int nr_bytes_total;    /* How many bytes does the current event type include? */
  unsigned char data[FLUID_MIDI_PARSER_MAX_DATA_SIZE]; /* The parameters or SYSEX data */
  fluid_midi_event_t event;        /* The event, that is returned to the MIDI driver. */
};

int fluid_isasciistring(char* s);
long fluid_getlength(unsigned char *s);


#endif /* _FLUID_MIDI_H */
