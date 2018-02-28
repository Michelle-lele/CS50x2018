// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <math.h>

#include "helpers.h"

#define EIGHT 8 //eight duration
#define D_OCTAVE 4 //default octave is 4
#define A4HZ 440 //A4 note frequency
#define CNOTE 9 //steps away from A note

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int nominator = fraction[0] - '0';
    int denominator = fraction[2] - '0';
    while (denominator < EIGHT)
    {
        nominator *= 2;
        denominator *= 2;
    }
    return nominator;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char letter;
    char accidental;
    int octave;
    float hz = A4HZ;
    int mult = 0;

    if (strlen(note) == 2)
    {
        letter = note[0];
        octave = note[1] - '0';
    }

    if (strlen(note) == 3)
    {
        letter = note[0];
        accidental = note[1];
        octave = note[2] - '0';

        //Converts flat accidental note to sharp accidental note
        if ((letter == 'D' || letter == 'd' || letter == 'E' || letter == 'e'  || letter == 'G' || letter == 'g' || letter == 'A'
        || letter == 'a'  || letter == 'B' || letter == 'b') && (accidental == 'b' || accidental == 'b'))
        {
            if (letter == 'A' || letter == 'a')
            {
                note[0] = 'G';
            }

            else
            {
                note[0] -= 1;
            }
            note[1] = '#';
        }
    }

    //Returns 440hz if not is A4
    if (note[0] == 'A' && note[1] == '4')
    {
        return hz;
    }

    //Calculates frequency of A note of corresponding octave
    mult = octave - D_OCTAVE;
    if (mult < 0)
    {
        mult = -mult;
        //printf("Mult is: %i\n", mult);
        hz /= pow(2, mult);
        //printf("A note is: %f\n", hz);
    }
    else
    {
        hz *= pow(2, mult);
        //printf("Mult is: %i\n", mult);
        //printf("A note is: %f\n", hz);
    }

    //Calculates frequency of C note of corresponding octave
    hz /= pow(2, (CNOTE / 12.00));
    //printf("C note is: %f\n", hz);

    //find how many notes away from C note is inputted note
    letter = note[0];
    accidental = (strlen(note) == 3);

    if (accidental)
    {
        octave = note[2];
    }
    else
    {
        octave = note[1];
    }

    string notes[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    int count = 0;
    for (int i = 0; i < 12; i++) //todo notes.size
    {
        if (letter==notes[i][0])
        {
            count = i;
            //printf("Note is: %s\n", notes[i]);
            //printf("Count is: %i\n", count);

            if (accidental)
            {
                count ++;
                //printf("Count is: %i\n", count);
            }
            break;
        }
    }
    // printf("Count is: %i\n", count);

    hz *= (pow(2, (count / 12.0)));
    int Hz;
    return Hz = round(hz);
}


// Determines whether a string represents a rest
bool is_rest(string s)
{
    string nothing = "";
    if (strlen(s) == strlen(nothing))
    {
        if(nothing[0] == s[0])
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
