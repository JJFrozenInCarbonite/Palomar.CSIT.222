#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define NTRAINS 4
#define NTRACKS 2
#define NSEGS 10
#define CW 1
#define CCW -1
#define NSIMS 50

struct Segment 
{
    int train = 0; // 0 is empty, +1 is clockwise, and -1 is counter clockwise
    Segment* next; // next segment when moving clockwise
    Segment* prev; // next segment whenmoving counter clockwise
    Segment* nextOther; // next segment on other track when moving clockwise
    Segment* prevOther; // next segment on other track when moving counter clockwisse
};

class Track 
{
public:
    // member variables
    std::vector<Segment> segments;

    // constructor
    Track(int size): segments(size) 
    {
        // Initialize the track
        for (int i = 0; i < size; ++i) 
        {
            segments[i].next = &segments[(i + 1) % size];
            segments[i].prev = &segments[(i - size - 1) % size];
        }
    }

    /**
     * This function links the track segment nodes of this track to the track
     * segment nodes of another track
     * 
     * @param targetTrack another track to link to this track
    */
    void linkTracks(Track& targetTrack)
    {
        int size = segments.size();
        for(int i = 0; i < segments.size(); ++i)
        {
            segments[i].nextOther = &targetTrack.segments[(i + 1) % size];
            segments[i].prevOther = &targetTrack.segments[(i - 1 + size) % size];
            targetTrack.segments[(i + 1) % size].nextOther = &segments[i];
            targetTrack.segments[(i - 1 + size) % size].prevOther = &segments[i];
        }
    }
};

void populateTrains(std::vector<Track>& tracks)
{
    int i = 0;
    while (i < NTRAINS)
    {
        int direction = rand() % 2 ? 1 : -1; 
        int track = rand() % NTRACKS;
        int segment = rand() % NSEGS;

        if (tracks[track].segments[segment].train == 0)
        {
            tracks[track].segments[segment].train = direction;
            i++;
        }   
    }
}

void moveTrains(std::vector<Track>& tracks)
{
    std::vector<Segment> segments;
    for(int i = 0; i < NTRACKS; i++)
    {
        for (int j = 0; j < NSEGS; j++)
        {
            if (tracks[i].segments[j].train != 0)
                segments.push_back(tracks[i].segments[j]);
        }
    }

    for (auto& segment: segments)
    {
        if(
            segment.train == CW 
            && segment.next->train == 0)
        {
            segment.train = 0;
            segment.next->train = CW;
        }
        else if (
            segment.train == CW 
            && segment.next->train == CCW 
            && segment.nextOther->train == 0)
        {
            segment.train = 0;
            segment.nextOther->train = CW;
        }
        else if (
            segment.train == CCW
            && segment.prev->train == 0)
        {
            segment.train = 0;
            segment.prev->train = CCW;
        }
        else if (
            segment.train == CCW
            && segment.prev->train == CW
            && segment.prevOther->train == 0)
        {
            segment.train = 0;
            segment.prevOther->train = CCW;
        }
    }
}

std::vector<std::string> mapTrains(const std::vector<Track>& track)
{
    
    std::vector<std::string>results;
    
    for (int i = 0; i < NTRACKS; i++)
    {
        results.push_back(" ");
        for (int j = 0; j < NSEGS / 2; j++)
        {
            if (j < 5)
                if (track[i].segments[j].train == CW)
                    results[i] += "->-";
                else if (track[i].segments[j].train == CCW)
                    results[i] += "-<-";
                else
                    results[i] += "---"
                
                
        }
    }

    return results;
}

void printTrains(const std::vector<Track>& tracks)
{
    std::vector<std::string> trainMap = mapTrains(tracks);
    /*
    std::cout << "+ " << printSegments(tracks[0]) << "  +\n";
    std::cout << "|   X   X   X   X   X   |\n";
    std::cout << "|+" << printSegments(tracks[1]) << " +|\n";
    std::cout << "||                     ||\n";
    std::cout << "|+" << printSegments(tracks[1]) << " +|\n";
    std::cout << "|   X   X   X   X   X   |\n";
    std::cout << "+ " << printSegments(tracks[0]) << "  +\n\n";    
    */
}



int main() 
{
    std::vector<Track> tracks;

    for(int i = 0; i < NTRACKS; i++)
        tracks.push_back(Track(NSEGS));
 
    tracks[0].linkTracks(tracks[1]);
    
    srand(static_cast<unsigned>(time(nullptr)));
    
    populateTrains(tracks);
    printTracks(tracks);

    for (int i = 0; i < 4; i++);
    {
        moveTrains(tracks);
        printTracks(tracks);
    }

}