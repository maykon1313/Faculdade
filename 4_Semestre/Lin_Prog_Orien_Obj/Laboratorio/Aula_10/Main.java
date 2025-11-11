package Aula_10;

import javax.sound.midi.*;
import static javax.sound.midi.ShortMessage.*;

public class Main {
    public static void main(String[] args) {
        Main teste = new Main();
        teste.play();
    }

    public void play() {
        try {
            Sequencer sequencer = MidiSystem.getSequencer();
            System.out.println("Entrou no Try.");
            sequencer.open();

            Sequence seq = new Sequence(Sequence.PPQ, 4);
            Track track = seq.createTrack();

            long tick = 1;
            for (int i = 0; i <= 1000; i++) {
                ShortMessage msg1 = new ShortMessage();
                msg1.setMessage(NOTE_ON, 1, (44+i)%84, 100);
                MidiEvent noteOn = new MidiEvent(msg1, tick);
                track.add(noteOn);

                ShortMessage msg2 = new ShortMessage();
                msg2.setMessage(NOTE_OFF, 1, (44+i)%84, 100);
                MidiEvent noteOff = new MidiEvent(msg2, tick);
                track.add(noteOff);

                tick += 1;
            }
            
            sequencer.setSequence(seq);
            sequencer.start();
        }

        catch (MidiUnavailableException | InvalidMidiDataException e) {
            System.out.println("Erro, aqui ó.");
            e.printStackTrace();
        }
    }
}