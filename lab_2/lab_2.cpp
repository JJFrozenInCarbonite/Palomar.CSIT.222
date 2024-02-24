/**
 * Lab 2
 *
 * A simulation of trains moving on a circular track with possibilities of switching 
 * between parallel tracks.
 *
 * @author JJ Hoffmann
 * @version 2024-02-24
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

#define NTRAINS 4 // Number of trains
#define NTRACKS 2 // Number of tracks
#define NSEGS 10 // Number of segments per track
#define CW 1 // Clockwise movement indicator
#define CCW -1 // Counter-clockwise movement indicator
#define NSIMS 50 // Number of simulations to run

/**
 * Struct representing a segment of a track.
 * Each segment can hold information about a train, its track, and its position in the track.
 * It also has pointers to adjacent segments on the same track and parallel segments on another track.
 */
struct Segment {
    int train = 0; // Train indicator
    int track = -1; // Identifier of the track to which the segment belongs
    int segment = -1; // Position of the segment within its track
    Segment* next; // Pointer to the next segment on the same track
    Segment* prev; // Pointer to the previous segment on the same track
    Segment* nextOther; // Pointer to the next segment on another track
    Segment* prevOther; // Pointer to the previous segment on another track
};

/**
 * Class representing a circular track composed of segments.
 * Provides functionality to link segments within the track and to link parallel tracks 
 * for train movement across tracks.
 */
class Track {
    public:
        Segment segments[NSEGS]; // Array of segments composing the track.

    /**
     * Constructor initializes the track by linking each segment to its adjacent segments.
     */
    Track() {
        for(int i = 0; i < NSEGS; i++) {
            segments[i].next = &segments[(i + 1) % NSEGS];
            segments[i].prev = &segments[(i - 1 + NSEGS) % NSEGS];
        }
    }

    /**
     * Links the segments of this track to the segments of another track, allowing for 
     * cross-track movement.
     * 
     * @param track Reference to another track to link with.
     */
    void linkTracks(Track& track) {
        for(int i = 0; i < NSEGS; i++) {
            segments[i].nextOther = &track.segments[(i + 1) % NSEGS];
            segments[i].prevOther = &track.segments[(i - 1 + NSEGS) % NSEGS];
            track.segments[i].nextOther = &segments[(i + 1) % NSEGS];
            track.segments[i].prevOther = &segments[(i - 1 + NSEGS) % NSEGS];
        }
    }
};

/**
 * Populates the tracks with trains in random segments and directions.
 * 
 * @param tracks Array of tracks to populate.
 */
void populateTrains(Track (&tracks)[NTRACKS]);

/**
 * Displays the current state of the tracks and trains.

 * @param tracks Array of tracks to display.
 */
void displayTrains(const Track (&tracks)[NTRACKS]);

/**
 * Moves trains along and between tracks based on their current direction and position.
 * 
 * @param tracks Array of tracks containing the trains to move.
 */
void moveTrains(Track (&tracks)[NTRACKS]);


/**
 * The main function initializes tracks, populates them with trains, and runs simulations 
 * to move trains and display their states.
 * 
 * @return int Returns 0 on successful execution.
 */
int main() {

    Track tracks[NTRACKS];

    for(int i = 0; i < NTRACKS - 1; i++)
        tracks[i].linkTracks(tracks[i + 1]);

    for(int i = 0; i < NTRACKS; i++) {
        for(int j = 0; j < NSEGS; j++) {
            Segment* temp = &tracks[i].segments[j];
            temp->track = i;
            temp->segment = j;
        }
    }

    populateTrains(tracks);

    for(int i = 0; i < NSIMS; i++) {
        std::cout << "Sim " << i + 1 << ":\n";
        displayTrains(tracks);
        moveTrains(tracks);
        
    }
    
    return 0;
}

void populateTrains(Track (&tracks)[NTRACKS]) {
    
    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = CCW; i <= CW; i += 2) {
        int j = 0;
        while (j < NTRAINS /  2) {
            int t = rand() % NTRACKS;
            int s = rand() % NSEGS;
            if (tracks[t].segments[s].train == 0) {
                tracks[t].segments[s].train = i;
                j++;
            }
        }
    }
}

void displayTrains(const Track (&tracks)[NTRACKS]) {
    int lines = (NTRACKS * 2) + 1; // total number of lines to be displayed
    int rows = NSEGS / 2; // half of each track is used per line to create a loop of track

    for(int i = 0; i < lines; i++) {
        
        std::string str; // initialize empty string for each line
        
        for (int j = 0; j < rows; j++) {

            if (!(i % (NTRACKS * 2))) {
                if (j == 0)
                    str += "+-";
                
                if (i < NTRACKS / 2) {
                    switch (tracks[i].segments[j].train) {
                        case CW:
                            str += "->-";
                            break;
                        case CCW:
                            str += "-<-";
                            break;
                        default:
                            str += "---";
                    }
                }
                if (i > NTRACKS / 2 ) {
                    switch (tracks[(i % (lines - 1))].segments[NSEGS - j - 1].train) {
                        case CW:
                            str += "-<-";
                            break;
                        case CCW:
                            str += "->-";
                            break;
                        default:
                            str += "---";
                    }
                }
    
                if (j == rows - 1)
                    str += "-+";
            }
            else if (i % NTRACKS) {
                if (j == 0)
                    str += "|+";
                
                if (i < NTRACKS) {
                    switch (tracks[i].segments[j].train) {
                        case CW:
                            str += "->-";
                            break;
                        case CCW:
                            str += "-<-";
                            break;
                        default:
                            str += "---";
                    }
                }
                if (i > NTRACKS) {
                    switch (tracks[i % NTRACKS].segments[NSEGS - j - 1].train) {
                        case CW:
                            str += "-<-";
                            break;
                        case CCW:
                            str += "->-";
                            break;
                        default:
                            str += "---";
                    }
                }

                if (j == rows - 1)
                    str += "+|";
            }
            else 
                str ="|| X  X  X  X  X ||";
            /*
              0  +-----------------+
              1  |+---------------+|
              2  || X  X  X  X  X ||
              3  |+---------------+|
              4  +-----------------+
            */
        }
        std::cout << str << std::endl;
    }
}

void moveTrains(Track (&tracks)[NTRACKS]) {
    
    Segment* segments[NTRAINS]; // Array of segments to hold individual segments of tracks containing trains for future evaluation

    int i = 0;
    for(auto& track : tracks) {
        for(auto& segment: track.segments) {
            if (segment.train != 0) {
                segments[i] = &segment;
                i++;
            }
        }
    }

    for(auto& segment : segments) {
        if (segment->train == CW) {
            Segment* next = segment->next;
            if (next->train == 0) {
                next->train = segment->train;
                segment->train = 0;
            }
            else {
                Segment* nextOther = segment->nextOther;
                if (nextOther->train == 0) {
                    nextOther->train = segment->train;
                    segment->train = 0;
                }
            }
        }
        if (segment->train == CCW) {
            Segment* prev = segment->prev;
            if (prev->train == 0) {
                prev->train = segment->train;
                segment->train = 0;
            }
            else {
                Segment* prevOther = segment->prevOther;
                if (prevOther->train == 0) {
                    prevOther->train = segment->train;
                    segment->train = 0;
                }
            }
        }
    }
}