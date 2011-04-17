#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "src/whysynth_voice_render.c"

// set CHECK_OUTPUT to true when you want to use the LONG_SEGMENT_LENGTH to
// check the filter output by ear
#define CHECK_OUTPUT
#define LONG_SEGMENT_LENGTH 2750
#define SHORT_SEGMENT_LENGTH 64

#define FREQ_STEPS 10
#define RES_STEPS 20

// These defines give us a header for a 44.1kHz 16 bit mono WAV file
#ifdef CHECK_OUTPUT
  #define DATA_SIZE (LONG_SEGMENT_LENGTH * FREQ_STEPS * RES_STEPS * 2)
#else
  #define DATA_SIZE (SHORT_SEGMENT_LENGTH * FREQ_STEPS * RES_STEPS * 2)
#endif

#define WAV_HEADER  { \
0x57, 0x41, 0x56, 0x45, 0x66, 0x6d, 0x74, 0x20,  0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, \
0x44, 0xac, 0x00, 0x00, 0x88, 0x58, 0x01, 0x00,  0x02, 0x00, 0x10, 0x00, 0x64, 0x61, 0x74, 0x61 \
}
#define WAV_HEADER_SIZE 32
#define WAV_FILESIZE (10 + WAV_HEADER_SIZE + DATA_SIZE)

void test_filter(uint32_t length, float freq, float key_mod, float res, FILE *output)
{
    int i;
    float fzero = 0.0f;

    struct vvcf  vcf_state = {0, 0, 0.0, 0.0, 0.0, 0.0, 0.0};
    y_voice_t   *voice     = malloc(sizeof(y_voice_t));
    y_svcf_t    *param     = malloc(sizeof(y_svcf_t));

    param->frequency = &key_mod;
    param->qres = &res;

    param->mode = &fzero;
    param->source = &fzero;
    param->freq_mod_src = &fzero;
    param->freq_mod_amt = &fzero;
    param->mparam = &fzero;

    float in[length]; 
    float out[length];

    // TODO only call this for automated tests to prevent audible patterns forming
    // when verifying the output by ear
    //srand(0);

    for (i = 0; i < length; i++)
    {
        in[i] = ((float)random() / (float)RAND_MAX) - 0.5f;
        out[i] = 0;
    }


    vcf_2pole(length, param, voice, &vcf_state, freq, (float *)&in, (float *)&out);

    int16_t audio[length];
    for (i = 0; i < length; i++)
        audio[i] = (int16_t)roundf(out[i] * 25000 );

    fwrite(audio, 2, length, output);


    // TODO check return values
}

FILE *create_wav(char *filename)
{
    FILE *output = fopen(filename,"wb");

    int riff_size = WAV_FILESIZE - 8;
    fwrite("RIFF", 1, 4, output);
    fwrite(&riff_size, 4, 1, output);

    uint8_t header[] = WAV_HEADER;
    fwrite(&header, 1, 32, output);

    uint32_t data_size = DATA_SIZE;
    fwrite(&data_size, 4, 1, output);

    return output;
}

int main(void) 
{
    // freq: 0-50 from GUI
    // svcf->frequency: ~0.001-0.05 from note value (middle C ~ 0.0055)
    // res: 0-1

    FILE *output = create_wav("filter_sweep_test.wav");

    float freq,r;

#ifdef CHECK_OUTPUT
    const uint32_t test_segment_length = LONG_SEGMENT_LENGTH;
#else
    const uint32_t test_segment_length = SHORT_SEGMENT_LENGTH;
#endif

    for (r=0; r < 0.9; r += (1.0/RES_STEPS))
        for (freq=0; freq < FREQ_STEPS; freq++)
            test_filter(test_segment_length, freq, 0.0055, r, output);

    fclose(output);

    return 0;
}
