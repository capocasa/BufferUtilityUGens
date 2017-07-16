
BufferRate : UGen {
  *ar {
    thisMethod.shouldNotImplement;
  }
	*kr { arg bufnum=0, trigger=1.0, samplerate=48000.0, doneAction=0;
		^this.multiNew('control', bufnum, trigger, samplerate, doneAction)
	}
}

