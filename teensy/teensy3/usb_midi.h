#ifndef USBmidi_h_
#define USBmidi_h_

#if defined(USB_MIDI)

#include <inttypes.h>

// MIDI Constants
#define NoteOff 0
#define NoteOn 1
#define AfterTouchPoly 2
#define ControlChange 3
#define ProgramChange 4
#define AfterTouchChannel 5
#define PitchBend 6
#define SystemExclusive 7
#define USB_MIDI_SYSEX_MAX 60  // maximum sysex length we can receive

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
void usb_midi_write_packed(uint32_t n);
void usb_midi_send_sysex(const uint8_t *data, uint32_t length);
void usb_midi_flush_output(void);
int usb_midi_read(uint32_t channel);
extern uint8_t usb_midi_msg_channel;
extern uint8_t usb_midi_msg_type;
extern uint8_t usb_midi_msg_data1;
extern uint8_t usb_midi_msg_data2;
extern uint8_t usb_midi_msg_sysex[USB_MIDI_SYSEX_MAX];
extern uint8_t usb_midi_msg_sysex_len;
extern void (*usb_midi_handleNoteOff)(uint8_t ch, uint8_t note, uint8_t vel);
extern void (*usb_midi_handleNoteOn)(uint8_t ch, uint8_t note, uint8_t vel);
extern void (*usb_midi_handleVelocityChange)(uint8_t ch, uint8_t note, uint8_t vel);
extern void (*usb_midi_handleControlChange)(uint8_t ch, uint8_t control, uint8_t value);
extern void (*usb_midi_handleProgramChange)(uint8_t ch, uint8_t program);
extern void (*usb_midi_handleAfterTouch)(uint8_t ch, uint8_t pressure);
extern void (*usb_midi_handlePitchChange)(uint8_t ch, int pitch);
extern void (*usb_midi_handleRealTimeSystem)(uint8_t rtb);

#ifdef __cplusplus
}
#endif

// C++ interface
#ifdef __cplusplus
class usb_midi_class
{
        public:
        void begin(void) { }
        void end(void) { }
        void sendNoteOff(uint32_t note, uint32_t velocity, uint32_t channel) __attribute__((always_inline)) {
		usb_midi_write_packed(0x8008 | (((channel - 1) & 0x0F) << 8)
		  | ((note & 0x7F) << 16) | ((velocity & 0x7F) << 24));
	}
        void sendNoteOn(uint32_t note, uint32_t velocity, uint32_t channel) __attribute__((always_inline)) {
		usb_midi_write_packed(0x9009 | (((channel - 1) & 0x0F) << 8)
		  | ((note & 0x7F) << 16) | ((velocity & 0x7F) << 24));
	}
        void sendPolyPressure(uint32_t note, uint32_t pressure, uint32_t channel) __attribute__((always_inline)) {
		usb_midi_write_packed(0xA00A | (((channel - 1) & 0x0F) << 8)
		  | ((note & 0x7F) << 16) | ((pressure & 0x7F) << 24));
	}
        void sendControlChange(uint32_t control, uint32_t value, uint32_t channel) __attribute__((always_inline)) {
		usb_midi_write_packed(0xB00B | (((channel - 1) & 0x0F) << 8)
		  | ((control & 0x7F) << 16) | ((value & 0x7F) << 24));
	}
        void sendProgramChange(uint32_t program, uint32_t channel) __attribute__((always_inline)) {
		usb_midi_write_packed(0xC00C | (((channel - 1) & 0x0F) << 8)
		  | ((channel & 0x7F) << 16));
	}
        void sendAfterTouch(uint32_t pressure, uint32_t channel) __attribute__((always_inline)) {
		usb_midi_write_packed(0xD00D | (((channel - 1) & 0x0F) << 8)
		  | ((pressure & 0x7F) << 16));
	}
        void sendPitchBend(uint32_t value, uint32_t channel) __attribute__((always_inline)) {
		usb_midi_write_packed(0xE00E | (((channel - 1) & 0x0F) << 8)
		  | ((value & 0x7F) << 16) | ((value & 0x3F80) << 17));
	}
        void sendSysEx(uint32_t length, const uint8_t *data) {
		usb_midi_send_sysex(data, length);
	}
        void send_now(void) {
		usb_midi_flush_output();
	}
        uint8_t analog2velocity(uint16_t val, uint8_t range);
        bool read(uint8_t channel=0) {
		return usb_midi_read(channel);
	}
        inline uint8_t getType(void) {
                return usb_midi_msg_type;
        };
        inline uint8_t getChannel(void) {
                return usb_midi_msg_channel;
        };
        inline uint8_t getData1(void) {
                return usb_midi_msg_data1;
        };
        inline uint8_t getData2(void) {
                return usb_midi_msg_data2;
        };
        inline uint8_t * getSysExArray(void) {
                return usb_midi_msg_sysex;
        };
        inline void setHandleNoteOff(void (*fptr)(uint8_t channel, uint8_t note, uint8_t velocity)) {
                usb_midi_handleNoteOff = fptr;
        };
        inline void setHandleNoteOn(void (*fptr)(uint8_t channel, uint8_t note, uint8_t velocity)) {
                usb_midi_handleNoteOn = fptr;
        };
        inline void setHandleVelocityChange(void (*fptr)(uint8_t channel, uint8_t note, uint8_t velocity)) {
                usb_midi_handleVelocityChange = fptr;
        };
        inline void setHandleControlChange(void (*fptr)(uint8_t channel, uint8_t control, uint8_t value)) {
                usb_midi_handleControlChange = fptr;
        };
        inline void setHandleProgramChange(void (*fptr)(uint8_t channel, uint8_t program)) {
                usb_midi_handleProgramChange = fptr;
        };
        inline void setHandleAfterTouch(void (*fptr)(uint8_t channel, uint8_t pressure)) {
                usb_midi_handleAfterTouch = fptr;
        };
        inline void setHandlePitchChange(void (*fptr)(uint8_t channel, int pitch)) {
                usb_midi_handlePitchChange = fptr;
        };
        inline void setHandleRealTimeSystem(void (*fptr)(uint8_t realtimebyte)) {
                usb_midi_handleRealTimeSystem = fptr;
        };
	private:
};

extern usb_midi_class usbMIDI;


#endif // __cplusplus

#endif // USB_MIDI
#endif // USBmidi_h_

