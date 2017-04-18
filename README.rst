WhySynth
~~~~~~~~

A software synthesizer plugin  for the DSSI Soft Synth Interface

Introduction
============
WhySynth is a versatile softsynth which operates as a plugin for the
DSSI Soft Synth Interface.  A brief list of features:

- 4 oscillators, 2 filters, 3 LFOs, and 5 envelope generators per
  voice.

- 11 oscillator modes: minBLEP, wavecycle, chorused wavecycle,
  asynchronous granular, three FM modes, waveshaper, noise,
  PADsynth, and phase distortion.

- 10 filter modes.

- flexible modulation and mixdown options, plus effects.

DSSI is a plugin API for software instruments (soft synths) with
user interfaces, permitting them to be hosted in-process by audio
applications.  More information on DSSI can be found at:

  http://dssi.sourceforge.net/

WhySynth is something of a mongrel, combining bits from
`Xsynth-DSSI <http://dssi.sourceforge.net/download.html#Xsynth-DSSI>`_,
`hexter <http://dssi.sourceforge.net/hexter.html>`_,
Csound, Mats Olsson's MSS, and various other programs, with
inspiration from a number of my favorite long-hair-days synths
(Matrix 6, ESQ-1, K4), and wavecycle data resynthesized from Claude
Kaber's Virtual K4 samples and //christian's exegesis of the Ensoniq
SQ-80 wavetable ROMs. See the enclosed file AUTHORS for more
details.

WhySynth is written by Sean Bolton, and copyright (c) 2017 under the
GNU General Public License, version 2 or later.  See the enclosed
file `COPYING <COPYING>`_ for details.  While this software is 'free' within the
requirements of this license, I (Sean) would appreciate any or all
of the following should you find WhySynth useful:

- an email stating where you're from and how you're using
  WhySynth, sent to <whysynth /at/ smbolton /dot/ com>, or better
  yet, a postcard sent to:

  |   Sean Bolton
  |   14722 30th Ave NE
  |   Shoreline Washington 98155 USA

- copies of or links to music you've created with WhySynth.

- any patches you create for WhySynth. Yes! Please!

- suggestions for improving WhySynth.

The patches distributed with WhySynth, including the default
'factory' patches and those found in the 'extra' directory, have
been placed in the public domain by their respective authors.  See
the enclosed file `extra/COPYING-patches <extra/COPYING-patches>`_ for details.

The GUI is stiflingly dull.  Anyone want to help make it look cool?

Requirements
============
WhySynth requires the following:

- DSSI version 0.9 or greater, available from the
  dssi.sourceforge.net address above.

- liblo version 0.12 or greater (0.23 or greater recommended), a
  library implementing the Open Sound Control (OSC) protocol,
  available at:

      http://liblo.sourceforge.net/

- pkgconfig with PKG_CONFIG_PATH set appropriately to pick up
  DSSI and liblo.

- FFTW version 3, available at:

      http://www.fftw.org/

  (WhySynth contains code to use FFTW version 2, but it is
  untested and not supported.)

- GTK+ version 2.4 or later.  (If a suitable GTK+ installation
  is not found, the plugin will be built without the GUI.)

- the LADSPA v1.x SDK.

- the ALSA headers (DSSI plugins use ALSA structures, but not
  the actual drivers, so you don't necessarily need the
  drivers installed.)  Users of non-Linux systems can use
  libdssialsacompat, available at:

      http://smbolton.com/linux.html

- a working DSSI host.  WhySynth has been tested with
  jack-dssi-host, available in the DSSI distribution, and with
  ghostess, available at:

      http://smbolton.com/linux.html

- automake 1.7 and autoconf 2.57 or better if you wish to
  recreate the build files.

Installation
============
The generic installation instructions in the enclosed file INSTALL
aren't particularly helpful, so try this instead:

1. Unpack the tar file.

2. Make sure PKG_CONFIG_PATH is set correctly to locate the
   dssi.pc and liblo.pc pkgconfig files.  On many systems, this
   will be:

   .. code-block:: shell

      $ PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
      $ export PKG_CONFIG_PATH

3. 'cd' into the package directory and execute './configure'.
   configure will add '-Wall' and my favorite optimizations to
   CFLAGS for you if you don't include any '-Wall' or '-O' options.
   If you're using gcc and wish to provide your own optimization
   flags, you MUST at least use '-finline' and a non-zero '-O' flag
   to get decent results.

4. Enable debugging information if you desire: edit the file
   src/whysynth.h, and define Y_DEBUG as explained in the
   comments.
    
5. Do 'make'.  Hopefully it should build without warnings (or
   errors.)

6. 'make install' will install the following::

    <prefix>/lib/dssi/whysynth.so
    <prefix>/lib/dssi/whysynth/WhySynth_gtk
    <prefix>/share/whysynth/current_default_patches.WhySynth
    <prefix>/share/whysynth/more_K4_interpretations.WhySynth
    <prefix>/share/whysynth/version_20051005_patches.WhySynth
    <prefix>/share/whysynth/version_20051231_patches.WhySynth
    <prefix>/share/whysynth/version_20090608_patches.WhySynth
    <prefix>/share/whysynth/version_20100922_patches.WhySynth

7. You may wish to manually install the documentation as well: this
   README file, plus the files in the doc/ directory.

Feedback on your experiences building WhySynth is appreciated.

Operation
=========
To run the WhySynth plugin under the jack-dssi-host provided in the
DSSI distribution, I do the following:

1. Start JACK.

2. Start jack-dssi-host, supplying the correct plugin path
   and filename (substitute <prefix> as appropriate):

   .. code-block:: shell

      $ DSSI_PATH=<prefix>/lib/dssi jack-dssi-host whysynth.so

   jack-dssi-host should start, and moments later the WhySynth
   graphic user interface should appear.

3. Use aconnect, or qjackctl to connect jack-dssi-host to a MIDI
   source, such as vkeybd.

4. Begin playing sounds!  If you get no response, try clicking the
   'Send Test Note' button in the WhySynth GUI. This sends a note
   directly via the host to the plugin, so if you hear sound now,
   look for a problem between the example host and your MIDI
   source.  If you still don't hear sound, I'd look for a problem
   between the example host and your output device.  If you
   continue having trouble, you might recompile with Y_DEBUG bit 2
   set, which will cause the plugin to continuously output a quiet
   buzz to help debug your outgoing signal path.

WhySynth starts with a default set of sound presets, or 'patches',
that you can select either by selecting the GUI 'Patches' tab and
clicking on the patch name, or by sending a MIDI program change from
your MIDI source with the appropriate program number.

Main WhySynth Window
====================
Test Note
---------
The 'Test Note' controls allow you to send a test note to the
plugin, by clicking on the 'Send Test Note' button.  Changing the
'key' and 'velocity' sliders will change the pitch and velocity of
the test note.  A key of 60 is generally considered to be
'Middle C'.

Patches Tab
-----------
Selecting the 'Patches' tab displays a list of all the patches loaded.
Clicking on the name of a patch causes that patch to be selected.

Configuration Tab
-----------------
Tuning
    Sets the tuning of this instance of the plugin, as Hz for
    A-above-middle-C.

Polyphony
    Sets the maximum polyphony for this instance of the
    plugin.  If you attempt to play more notes than this setting,
    already-playing notes will be killed so that newer notes can be
    played.  If you are getting xruns, try reducing this setting.

Monophonic Mode
    'Off'
        polyphonic operation.
    'On'
        monophonic operation, where the envelopes are
        retriggered upon each incoming note on event. 
    'Once'
        monophonic operation, where the envelopes are triggered
        only on the first note on of a legato phrase -- that
        is, if you hold one note while playing a second, the
        envelopes will not be retriggered for the second note. 
    'Both'
        monophonic operation, where the envelopes are
        retriggered at each note on, and upon note off when
        other keys are still held.

Glide Mode
    'Legato Only'
        portamento (a 'slide' in pitch between two
        notes) is only used when a new note is played while
        another is held.
    'Non-legato Only'
        portamento is only used for single
        (staccato) notes, or the first note of a legato phrase.
    'Always'
        portamento is always used.
    'Leftover'
        like 'Always', but ... more difficult to predict.
    'Off'
        disables portamento.

Cancel Notes On Program Change
    This controls whether WhySynth will
    stop any playing notes before it performs a program change,
    which can prevent nasty surprises if the previous and new
    patches are not compatible.  Defaults to 'On'.

File Menu
---------
You may load additional patches by selecting 'Load Patch Bank...'
from the GUI 'File' menu, and pointing the file chooser dialog to a
WhySynth patch bank file.  Near the bottom of this dialog is a spin
button which allows you to specify the program number at which to
begin loading the new patches.  This allows you to overwrite the
existing patches, or to add the new patches at the end. WhySynth
will let you keep loading patches until you run out of memory, but
the most you can really use via MIDI would be 16384 patches (128
programs times 128 banks).

Selecting 'Save Patch Bank...' from the 'File' menu will allow you
to save your patch bank to a file.  A file chooser dialog will
appear, which you may use to specify a file name, as well as the
range of patches to be saved.

The 'Import Xsynth-DSSI Patches' menu option allows you to import
patches from WhySynth's predecessor, Xsynth-DSSI.  This conversion
is fairly accurate, but often needs a little hand tweaking,
especially where multiple modulators are used on the same
destination.  Like 'Load Patch Bank...', this import will ask for a
file name, then a program number at which to begin import patches.
You also have the option of importing the patches in 'dual' mode:
each set of oscillator parameters in the Xsynth-DSSI patch is
applied to two WhySynth oscillators (VCO1 to Osc1 and Osc3, VCO2 to
Osc2 and Osc4), and the Xsynth-DSSI filter settings are applied to
both WhySynth filters, with the busing and mixdown set to make
creation of stereo patches easy. Note that the import routine won't
do the stereo-ification for you -- you'll need to detune the
oscillators, or apply different modulation settings, in order to get
a stereo image.

The '(Mis)Interpret K4 Patches...' menu option will do a similar
import of Kawai K4 patches (from 15123-byte 'All Patch Data Dump'
system exclusive format).  Unfortunately, I don't own a K4, so I
have no way of making this function anything more than a wild guess.
Still, the results are sometimes interesting and useable.  Patches
which use PCM (non-single-cycle) samples or more than 4 unique sets
of envelope parameters will be skipped.  A 'dual' option is also
available for doubling up 'single' mode patches ('twin' and 'double'
modes need all four oscillators.) The default patch bank contains a
number of these interpreted K4 patches, and another 454 are
available in the included file extra/more_K4_interpretations.WhySynth.

Note that selecting 'Quit' from the 'File' menu just quits the
WhySynth GUI -- the host and plugin should continue to run.

Edit Menu
---------
Selecting a patch in the 'Patches' tab, then selecting 'Edit Patch...'
from the 'Edit' menu, opens the Patch Edit window....

Patch Edit Window
=================
This windows allows you to edit patches.

The 'Patch Name' text box allows you to change the name of a patch.
You may optionally add a comment to a patch in the 'Comment' box.

The controls in the Osc1, Osc2, Osc3, Osc4, Filters, Mix, Effect,
LFOs, and Miscellaneous tabs offer real-time control of the
synthesis parameters used by the plugin to create sound.  Only some
of the parameters on the EGO, EG1, EG2, EG3, and EG4 tabs are
real-time; some take effect at the beginning of the next envelope
segment, and some require a voice to be retriggered to take effect.
The voice architecture is described in more detail below.

The controls come in three varieties: rotary knobs, menu buttons,
and spin buttons.  The rotary knobs may be manipulated in several
ways:

- Clicking and dragging a knob with mouse button 1 sets the
  value directly, by making the knob pointer point toward the
  mouse pointer.
- Clicking and dragging a knob with mouse button 3 allows
  incremental adjustment of the knob's current value (without
  a sudden jump.) Horizontal movement produces large variation
  in the knob value, while vertical movement allows finer
  control.
- Clicking on a knob with buttons 1 and 3 increment and
  decrement the knob value.

Many of the bipolar patch parameters (whose values span zero,
such as the 'Detune' and 'Amp Mod Amount' controls) have a small
square button directly below the knob.  Clicking this button will
set the parameter directly to zero. A similar small button below the
Mix tab 'Pan' controls will set the panning directly to center.

The menu buttons may also be manipulated in several ways:

- Clicking the button with mouse button 1 will cause a menu of
  choices to pop up.  Clicking on one of the menu options will
  select that value, however, it can be rather difficult to
  audition the large number of choices using the mouse this
  way. You may prefer to use the keyboard:
- The button may be selected for keyboard input by clicking it
  with mouse button 2 or 3, or by repeatedly pressing the
  tab key until the button is highlighted.
- Once the button is selected for input, you may use the up
  arrow, down arrow, page-up and page-down keys to easily
  browse through the available options.

The 'Test Note' controls are similar to those of the main window,
with the additional of a small square check button.  If you click on
this button, then the 'Send Test Note' button becomes a sticky
'Toggle Test Note' button -- very handy for holding a note on while
twiddling knobs.

Once you have edited a patch to your satisfaction, you may save it
back to the patch bank by clicking the 'Save Changes' button.  You
will be asked to which program number you would like to save your
new patch.  If you do not wish to overwrite an existing patch,
selected the highest available patch number, next to which '(empty)'
will be displayed, to save your changes to a new slot.  Be sure to
then use 'Save Patch Bank...' from the 'File' menu to save your
changes to a file.

The oscillator, filter, effect and envelope generator tabs contain
'Copy' and 'Paste' buttons.  These buttons allow the settings for
their respective voice element to be copied to a 'clipboard', then
pasted into another element of the same type, possibly even in
another patch.

Voice Architecture
==================
In overview, each WhySynth voice consists of four oscillators, whose
output may be routed to two intermediate buses.  Two filters then
take their input from one or the other of these buses, or the second
filter can take its input from the first.  The two buses and the
filter outputs are then mixed down to stereo.  See the enclosed
image `doc/voice_block_diagram.png <doc/voice_block_diagram.png>`_ for a visual representation.

The stereo outputs for all active voices are summed, then passed
through a DC blocker (hard-synced minBLEP oscillators and waveshaper
oscillators can produce a lot of DC.)  The result can then be
optionally processed by an effects section, which at the moment
consists of either a plate reverb simulation or a dual delay.

MIDI information, three low-frequency oscillators (LFOs), and five
envelope generators are available for modulating oscillator and
filter parameters, and many of the modulators can themselves be
modulated by other modulators.

Oscillators
-----------
Each of the four oscillators may be operated in one of ten modes,
or turned off.  All of the modes have eight common controls:

- 'Pitch' and 'Detune' control the fundamental pitch of the
  oscillator, relative to the MIDI key. The former is in
  semitones, the latter in cents.

- 'Bus A Send Level' and 'Bus B Send Level' control the amount of
  the oscillator's output sent to each bus.

- 'Pitch Mod[ulator] Source', 'Pitch Mod Amount', 'Amp[litude] Mod
  Source', and 'Amp Mod Amount' allow selection of a modulation
  source and amount for the oscillator pitch and output level.

All of the modes also have a 'Waveform' control, whose meaning
depends upon the mode, plus zero to four additional mode-dependent
controls.  For many of the modes, the 'Waveform' control selects one
of some 168 different single-cycle 'wavecycle' waveforms.  See the
enclosed file doc/wavetable_guide for more information on these
waveforms.

The ten oscillator modes and their controls are:

1.  Asynchronous Granular - In this mode, the oscillator output is
    generated from many small bursts, or 'grains' of sound.  The
    'Waveform' control selects the wavecycle waveform used as the
    grain source.  The additional controls in this mode are:

    - 'Grain Lz' controls the average number of grains being summed
      to create the sound at any one moment.  The higher this
      setting, the more complex the resulting sound, but also the
      more CPU resources used!

    - 'Grain Spread' controls the amount of random deviation in the
      start times of each grain.

    - 'Grain Envelope' controls the length and shape of each grain.
      'Gaussian' is the typical bell curve, 'Rectangular' is just
      that, and (Curtis) 'Roadsian' smoothly splices gaussian ends
      on a rectangular middle.

    - 'Grain Freq Dist[ribution]' controls the random deviation in
      the frequency of each grain.

2.  'FM Wave->Sine' Phase Modulation - The classic 'FM' synthesis
    technique invented by John Chowning and popularized by the
    Yamaha DX-7, with a twist.  Here, one of the wavecycle waveforms
    is used to modulate a sine wave.  Additional controls are:

    - 'Mod Freq Ratio' sets the ratio of the modulator and carrier
      frequencies from 0.5 to 1 when fully counter-clockwise, in
      integer steps up to 16 to 1 when fully clockwise.

    - 'Mod Freq Detune' offers (very) fine tuning of the frequency
      ratio.

    - 'Mod Index Source' and 'Mod Index Amount' control the depth
      of the phase modulation.

3. 'FM Sine->Wave' Phase Modulation - As above, but here a sine wave
   is used to modulate one of the wavecycle waveforms.

4. 'FM Wave->LF Sine' Phase Modulation - One of the wavecycle
   waveforms is used to modulate a very-low-frequency sine wave,
   yielding an effect somewhat like a rotating speaker cabinet.
   The additional controls for this mode are:

   - 'Low Frequency' sets the frequency of the carrier sine wave,
     from 1/8Hz to 2Hz.

   - 'Mod Index Bias' sets a constant depth of modulation, to which
     is added the variable modulation depth determined by the
     'Mod Index Source' and 'Mod Index Amount' controls.

5. minBLEP - This mode uses the minBLEP technique for generating
   classic-analog waveforms with very little aliasing. The
   available waveforms are:

   0. Sawtooth+
   1. Sawtooth-
   2. Rectangular
   3. Triangular
   4. Clipped Saw
   5. Sample/Hold Noise (think '80s video game)

   minBLEP oscillators may be 'hard synced' to the previous
   (lower-numbered) oscillator by setting the 'Sync' control fully
   to 1.  See the discussion of synchronization below for more
   information.

   The Rectangular and S/H Noise waveforms also feature pulsewidth
   and pulsewidth modulation settings, the Triangular waveform has
   slope and slope modulation controls, and the Clipped Saw
   waveform has tooth width and tooth width modulation controls.
   Beware of overmodulating a Triangular wave's slope; it can
   produce a loud 'pop' which I haven't yet found a fast way of
   avoiding.

6. Noise - This mode comes in four flavors:

   0. White noise
   1. Pink noise
   2. Low-pass filtered white noise
   3. Band-pass filtered white noise

   For the last two, additional controls are provided for the
   filter cutoff/center frequency, and resonance.

7. PADsynth - An implementation of Nasca O. Paul's 'PADsynth'
   bandwidth-enhanced additive synthesis algorithm.  This mode
   takes the spectral profile of the source wavecycle waveform,
   spreads each partial over a range of frequencies, then
   resynthesizes the waveform to create very harmonically rich
   sound.

   Two important differences between this mode and the previous
   modes are that the resynthesis is not done in 'real time', and
   the resulting sound samples use a significant amount of memory.
   When you select a PADsynth patch, or make changes to one, it can
   take up to several seconds before the resynthesized sound is
   available (until which time WhySynth will substitute a simple
   sine wave.) Depending on the number of multisamples the
   wavecycle has, the resulting sound can take up to 3.5 megabytes
   of memory *per oscillator*.  PADsynth multisamples rendered with
   the same parameters are shared between oscillators and WhySynth
   instances, but if the parameters are different, it's easy to
   have WhySynth eat up quite a bit of memory.

   The controls for this mode are:

   - 'Partial Width' sets the degree to which the energy of each
     partial in the source wavecycle is spread over a range of
     frequencies in the resulting sound.  Higher widths result in
     a thicker or more chorused sound.

   - 'Partial Stretch' controls the amount by which the frequency
     center of each source partial is adjusted up or down. Pianos
     and other sound sources with stiff vibrating elements have a
     slight positive stretch to their sound.  Very high or very
     low stretch values will result in metallic, clangorous, or
     ring-modulated sounds.  **Until you get a feel for what the
     PADsynth controls do, always start with this control near
     zero (straight up)**.

   - 'Width Scale / Mode' combines the partial width scaling
     parameter with the stereo/mono mode parameter.  Even
     numbered settings are stereo, which means that the sounds
     written to Bus A and Bus B form a stereo image if
     appropriately panned. The partial width scaling controls
     the degree to which the partial width is increased for
     higher partials.  Many natural sound sources scale at around
     100% -- that is, partial eight will have eight times the
     spread of the fundamental.  Lower scaling settings produce
     more synthetic timbres, while at higher settings the upper
     harmonics merge, creating 'noisy' or 'breathy' sounds.

   - 'Damping' controls the reduction in strength of higher source
     partials (sort of like a low pass filter).  Low settings
     result in a brighter sound.

8. Phase Distortion - This mode implements phase distortion
   synthesis similar to the Casio CZ-series synthesizers.  Various
   functions are used to speed or slow the phase progression of a
   sine oscillator, adding harmonics to the signal and producing a
   sound which is distinctly digital, yet often similar to classic
   analog sounds.

   - The 'Waveform' control selects the resulting waveform when bias
     or modulation is applied -- with zero bias and modulation, a
     sine wave is always produced.  The waveform may be either a
     single shape, such as 'Sawtooth' or 'Pulse', or dual shapes
     which alternate in successive cycles, such as 'Saw & Pulse'.
     The alternation of the two shapes causes the oscillator to
     sound an octave below normal.

   The additional controls in this mode are:

   - 'Mod Balance' is only available when using dual waveforms,
     when it controls the relative amount of distortion applied
     during each waveform's respective cycle.  For example, if
     the waveform selected is 'Saw & Pulse', and this control is
     one fourth of the way from '1st' to '2nd', then during the
     first, sawtooth cycle the oscillator will be twice as
     responsive to bias and modulation as during the second,
     pulse cycle.

   - 'Bias' sets the minimum level of phase distortion.

   - 'Mod Amt Source' and 'Mod Amt Amount' allow selection of a
     modulation source and amount to control, together with the
     'Bias' amount, the total depth of phase distortion.

9. Wavecycle - In this mode, the oscillator produces one of the 168
   or so different single-cycle waveforms.  See the enclosed file
   doc/wavetable_guide for more information on the waveforms.

   Wavecycle oscillators may also be 'hard synced' to the previous
   oscillator, but the minBLEP anti-aliasing used only compensates
   for amplitude changes, not slope changes, at the phase reset,
   and so they will alias more at higher frequencies than a minBLEP
   oscillator would.  The exception to this is waveform 0 'Sine 1',
   which does have slope delta compensation.

   Many of the waveforms are multi-sampled (for band limiting
   and/or formant preservation), and there is a 'Wave Sel[ect]
   Bias' control which may be used to bias the wavetable selection
   toward the higher key ranges, for lower harmonic content.

10. Wavecycle Chorus - This mode is similar to the previous
    'Wavecycle' mode, except that five copies of the waveform are
    generated simultaneously. The additional controls for this mode
    are:
    
    - 'Tuning Spread' sets the degree to which the pitch of each
      copy differs from the others.

    - 'Chorus Depth' determines the extent to which the additional
      copies are mixed into the oscillator's output. At fully
      counter-clockwise, only a single copy is mixed in, while
      when fully clockwise, all five copies are included.

11. Waveshaper - Classic waveshaping, with the wavecycle waveforms
    used as the transfer functions.  As of this writing (2005/12/31),
    only one of the waveforms was created specifically for the
    waveshaper, a (rather boring) Chebychev T5 function, yet many of
    the other waveforms can yield interesting results.  The
    additional controls in this mode are:

    - 'Phase Bias' adds a constant phase bias into the transfer
      function, allowing you to shift the 'zero phase' point of
      the wavecycle.

    - 'Mod Amt Bias' sets the minimum level of the sine wave input
      into the transfer function.

    - 'Mod Amt Source' and 'Mod Amt Amount' allow selection of a
      modulation source and amount for the transfer function input
      level.

Oscillator Synchronization
--------------------------
Oscillators in minBLEP and wavecycle modes have the ability to 'hard
sync' to another oscillator, so that the slave oscillator's phase
resets whenever the master oscillator completes a cycle.  Here are
the rules for using sync:

1. The oscillators are run in numeric order, from Osc1 through Osc4,
   and a lower-numbered master oscillator must provide sync for a
   higher-numbered slave.

2. FM, minBLEP, phase distortion, wavecycle, wavecycle chorus, and
   waveshaper oscillators can be masters.

3. Only minBLEP and wavecycle oscillators can be slaves.

4. Async granular, noise, and PADsynth oscillators neither generate
   nor use sync, and may appear between master and slave.

5. Multiple slaves may sync to one master.

6. Any master overwrites the previous master's sync.

Filters
-------
The two filters each may be operated in one of seven modes, or
turned off.  Filter 1 can take its input from Bus A or Bus B, and
Filter 2 can take its input from either bus, or from the output of
Filter 1. All filter modes have cutoff/center frequency, frequency
modulation, and resonance/bandwidth controls.  The filter modes are:

1. The 2-pole (12dB/octave) low-pass filter from Xsynth.

2. The 4-pole (24dB/octave) low-pass filter from Xsynth.

3. Fons Adriaensen's MVC LPF-3, modeled after the voltage-controlled
   lowpass filter invented by R. A. Moog.  This mode has an
   additional 'Drive' control which adjusts the level of the signal
   within the filter, thereby changing the intensity of its
   non-linear effects.

4. The 4-pole low-pass filter from amSynth.

5. A 4-pole low-pass filter with clipping.  This is two, 2-pole
   filter stages with a hard clipper before each stage.  A 'Drive'
   control adjusts the relative clipping threshold.

6. A 4-pole band-pass filter.

7. The 2-pole, constant-gain, 'resonz' band-pass filter from Csound.
   In this mode, the 'Bandwidth' control operates backwards, so
   that it has the same intuitive 'feel' as the 'Resonance' control
   in other modes: turn it counter-clockwise for wider bandwidths,
   clockwise for narrower.

8. A 2-pole high-pass filter.

9. A 4-pole high-pass filter.

10. A 4-pole band-reject filter.

Mix
---
The mix controls allow setting the output level and left/right pan
of each of Bus A, Bus B, Filter 1 output, and Filter 2 output. A
Master Volume control controls the level of the resulting left and
right outputs.

Note that final output level is also 'hard-wired' to the EGO
envelope generator.

Effects
-------
Three effects are available: Tim Goetze's Versatile Plate reverb
simulation, Sean Costello's Csound reverb, and a Dual Delay.  All
effects share a 'Mix' control, which sets the blend of wet (effect)
and dry (uneffected) signals.

The 'Plate Reverb' has these controls:

- 'Bandwidth' controls the amount of high frequency passed from the
  input into the reverb simulation.

- 'Tail' controls the length of the reverb tail.

- 'Damping' controls the attenuation of high frequencies
  within the reverb 'tank'.

The 'Dual Delay' has these controls:

- 'Feedback' controls how much of the delayed signals is fed back
  into the delay lines.

- 'Feed Across' controls how much of the left signal (including
  feedback) is fed into the right delay line, and vice versa for
  right signal into left delay line.  With zero Feed Across, the
  left and right channel delays are completely independent.  With
  full Feed Across, sounds will 'ping-pong' between the two
  channels.

- 'Left Delay' and 'Right Delay' set the left and right delay times,
  respectively.

- 'Damping' controls the attenuation of high frequencies going in to
  the delay lines.

The 'SC Reverb' has these controls:

- Greater 'Feedback' creates a longer reverb 'tail'.

- A higher 'Low Pass Freq' causes less damping of high frequencies.

- 'Pitch Mod' controls the amount of random pitch shift in the delay
  lines.

Modulation
==========
There are 23 different modulation sources available for every voice
modulation option mentioned above, plus each of the LFOs and
envelope generators can themselves be modulated.  Briefly, the
modulation sources are:

0.  Constant On
1.  Mod Wheel
2.  Pressure
3.  Key
4.  Velocity
5.  GLFO Bipolar
6.  GLFO Unipolar
7.  VLFO Bipolar
8.  VLFO Unipolar
9.  MLFO 0 Bipolar
10. MLFO 0 Unipolar
11. MLFO 1 Bipolar
12. MLFO 1 Unipolar
13. MLFO 2 Bipolar
14. MLFO 2 Unipolar
15. MLFO 3 Bipolar
16. MLFO 3 Unipolar
17. EGO
18. EG1
19. EG2
20. EG3
21. EG4
22. ModMix

The 'Constant On' modulation source always has a value of '1', or
fully on.

MIDI Modulators
---------------
1. Mod Wheel - This mod source takes the value of MIDI modulation
   wheel (control change #1).

2. Pressure - This mod source combines, for each voice, the MIDI
   channel pressure and key (polyphonic) pressure for the note.

3. Key - These mod is set to the note's key.

4. Velocity - This mod is set to the note's velocity.

LFOs
----
There are three low-frequency oscillators available for use as
modulators: an instrument-wide 'global' LFO (GLFO), a per-voice LFO
(VLFO), and another per-voice multi-phase LFO (MLFO), which is
actually four LFOs in one.

Each LFO has two outputs, a bipolar (-1 to 1) output, and a unipolar
(0 to 1) output.  As a rule of thumb, the bipolar outputs tend to be
best when modulating oscillator pitch or filter cutoff frequency,
and the unipolar outputs tend to be best when modulating amplitude.

Each LFO has a frequency control and a waveform selection control.
The LFOs use the same waveforms as the wavecycle oscillators, but
the wavetables also contain some non-bandlimited, Gibbs-effect-free
waveforms specifically intended for use with the LFOs. These appear
in the 'LFO' section of the wavetable pop-up menus.

Each LFO also has amplitude modulation source and amount controls.
Since the GLFO is one LFO shared by all voices within an WhySynth
instance, it does not have any of the per-voice modulation sources
available to it.

The VLFO and MLFO both have 'Delay' controls which set the time from
key-on that it takes the LFO to fade up to full strength.

The MLFO is actually four LFOs with a common set of controls.  The
'Phase Spread' control sets the initial phase difference, in
degrees, between successive MLFO LFOs, so that if this control is
set at 90, then MLFO 0 will start with a phase of 0 degrees, MLFO 1
with a phase of 90 degrees, MLFO 2 with 180, and MLFO 3 with 270. If
the 'Random Freq' control is zero, the MLFO LFOs will maintain this
phase difference over time.  Otherwise, 'Random Freq' controls the
random deviation in the individual LFOs frequencies, and their phase
differences will drift over time.

Envelope Generators
-------------------
There are five envelope generators per voice, each of which may be
run in one of five modes, and EGs EG1 through EG4 may also be turned
off.

The Output Envelope Generator EGO is special, in that the final
output amplitude of the voice is 'hard-wired' to be controlled by
the EGO level, and the voice is terminated when EGO reaches the end
of its final segment.

The five EG modes all have four segments, with four 'time' controls
setting the length of each segment, and three 'level' controls
setting the level of the envelope between each segment.  There are
also four 'shape' controls, which determine how the envelope level
changes within each segment.  'Lead' shapes at first approach the
segment's ending value more quickly than 'Linear' and then slow
their approach, 'Lag' shapes have slow initial approaches then
quickly arrive at the ending value.  'Hold' and 'Jump' are special
shapes which hold the segment's initial value for the duration of
the segment, and jump immediately to the segment's ending value,
respectively.  See the enclosed images doc/eg_shapes_*.png for
visual representations of the shapes:

    | `EG Shapes - Rising, Part 1 <doc/eg_shapes_rising_1.png>`_
    | `EG Shapes - Rising, Part 2 <doc/eg_shapes_rising_2.png>`_
    | `EG Shapes - Falling, Part 1 <doc/eg_shapes_falling_1.png>`_
    | `EG Shapes - Falling, Part 2 <doc/eg_shapes_falling_2.png>`_

The five EG modes are named:

1. ADSR
2. AAASR
3. AASRR
4. ASRRR
5. One-Shot

Modes 2, 3 and 4, run through their first three, two, and one
segments, respectively, before pausing until the key is released.
The knob labels in the GUI change with the mode to reflect this, so
that the level control at which this pause takes place is always
labeled 'Sustain Level'.  Once the key is released, the EG then
continues running through the remaining segments.

Mode 5, 'One-Shot', does not pause for a sustain, but continues
through all four segments regardless of the key on status.  Mode 1,
'ADSR', is just an AAASR envelope with some of the controls
greyed-out to provide the traditional and sometimes convenient
'ADSR' envelope.

Each envelope has five additional controls:

- 'Vel->Level' controls the sensitivity of the envelope levels to
  the key velocity. At a setting of 0, the envelope always goes to
  full output.  At maximum MIDI velocity (127), the envelope
  always goes to full output.  Otherwise, the lower the velocity
  and higher the sensitivity, the greater the reduction of the
  envelope's output.

- The 'Vel->Time', and 'Kbd->Time' control how the note velocity and
  key influence the envelope times. When these controls are set to
  positive amounts, the envelope times get shorter with higher
  velocities and keys; similarly, with negative settings, the
  times get longer with higher velocities and keys.

- 'Amp Mod Source' and 'Amp Mod Amount' allow the envelope output to
  be modulated by another modulator.

ModMix
------
On the 'Miscellaneous' tab, there are five controls for the 'ModMix'
modulation source.  This source actually takes two other modulation
sources, mixes their values together in adjustable amounts, and adds
an adjustable bias -- useful for when you need to modulate one
parameter with two different modulators.

Other Miscellaneous Controls
----------------------------
Also on the 'Miscellaneous' tab are 'Glide Rate' and 'Bend Range'
controls. The pitch from the MIDI key may be lagged by the 'Glide
Rate' value, as determined by the glide mode and other keys in play
(see above).  'Bend Range' sets the response to MIDI pitch bend, in
semitones.

MIDI Controller Mapping
=======================
For DSSI hosts that support MIDI controller mapping, WhySynth
requests that they map one MIDI controller:

- MIDI Control Change 5 "Portamento time" is mapped to the
  PORTAMENTO 'glide' control, although in a somewhat backward way:
  higher CC values map to shorter glide times, and lower CC values
  to longer glide times.

Other mappings can be configured by modifying the source code; see
the function y_get_midi_controller() in the file src/dssp_synth.c
for details.

WhySynth itself interprets several other MIDI control messages:

- MIDI Control Change 7 "Volume" controls the output level, without
  affecting the Master Volume control.

- MIDI Control Change 1 "Modulation wheel" is available as the "Mod
  Wheel" modulation source.

- MIDI channel pressure and key pressure are combined (per note) and
  available as the "Pressure" modulation source.

- MIDI Control Change 10 "Panning" controls panning of the output.

Questions That Might Be Frequently Asked
========================================

Q1. The plugin seems to work fine, but the GUI never appears. Why?

A1. Make sure the hostname of your machine is resolvable (if not, the
OSC messages can't be sent between host and GUI).  If your machine's
hostname is 'foo.bar.net', make sure you either have an entry for
'foo.bar.net' in /etc/hosts, or your DNS server can resolve it. Test
this with e.g. 'ping foo.bar.net'. To test that the GUI itself
works, you can start it by itself (without a DSSI host) by giving it
the '-test' option, for example:

.. code-block:: shell

   $ <prefix>/lib/dssi/whysynth/WhySynth_gtk -test

Q2. Help! I twist a knob, and get booted out of JACK!

A2. Particularly with the granular oscillators, it's really easy to
eat up lots of CPU with WhySynth. Some suggestions for making the
most of your setup:

- Use a recent version of JACK with a high '--timeout' value.
- Set the 'Polyphony' configuration setting to the minimum your
  work needs.
- Use the most efficient oscillator or filter mode that will get
  the sound you want: granular oscillators take the most CPU
  (proportional to the 'Grain Lz' setting), followed by
  PADsynth, waveshaper, FM, and wavecycle, with minBLEP
  oscillators taking the least. Fons' MVC LPF-3 filter takes
  more CPU than the other filters.
- Turn off any unused oscillators or EGs.
- Keep your EGO release times to a minimum, so active voices are
  turned off promptly.

Q3. Woah! Where'd that nasty sound come from?

A3. If the sound you're getting sucks more than you think it should,
check for the following:

- Volume too high: especially when using asynchronous granular
  oscillators, or high filter resonance, your signal may be so
  hot it's clipping.  Try reducing the oscillator bus send
  levels, the mix levels, and the master volume.
- YDB_AUDIO set: if you've got a ~600Hz buzz in the
  output even when you're not playing anything, your plugin
  was probably compiled with the XDB_AUDIO debug bit set.  Fix
  that and recompile.
- Pitch too high: even with the minBLEP oscillators, it is
  possible to get audible aliasing on very high notes.  This
  is especially true when using oscillator sync while the
  slave is producing a sine wave, since the band-limiting
  technique doesn't deal as well with waveforms having
  continuously varying slope.
- PADsynth 'Partial Stretch' too high or too low: if the stretch
  control is not close to zero (midway), very clangorous or
  metallic sounds result.

Q4. Help! My async granular patch sounds horribly out of tune, but
only sometimes.  What's wrong?

A4. Make sure your glide setting is completely off (for now, that's
fully clockwise to '1').  Even a very little glide with long grain
envelopes will cause the problem.

Q5. I upgraded from the 20100922 release to the 20120729 release, and
the default patches changed, breaking my super-cool setup.  What
gives?

A5. Just load the extra/version_20100922_patches.WhySynth file.

Q6. How can I map other MIDI control change (CC) or NRPN messages to
WhySynth ports?

A6. DSSI doesn't (yet) support run-time configuration of these
controller mappings, but you can set up your own mappings by editing
the function y_get_midi_controller() in the file src/dssp_synth.c,
then recompiling.  See the comments there for more information.

Q7. Uggh. The new cairo knobs look really nice, but they're too slow
on my remote X display.  What do I do?

A7. Change the line 'static int prefer_cairo = TRUE;' to FALSE in
gtkknob.c and recompile.
