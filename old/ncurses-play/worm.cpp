#include <iostream>
#include <string>
#include <chrono>
#include <ncurses.h>
using namespace std;
using namespace std::chrono_literals;
using std::chrono::high_resolution_clock;


class Writer {
    chtype character;
    int width;
    int height;
    int key;
    int random_direction; 
    int random_time; 
    int temporary_key;
    int color;

    public:
    Writer() {        
        srand (time(NULL)); // initialize random seed
        initscr();            /* Start curses mode  */
        timeout(15); // Amount of time for getch() to block.
        noecho();
        cbreak();
        curs_set(0);
//         color = 4;
        color = 1;
        
        if (has_colors() == FALSE) {
            endwin();
            printf("Your terminal does not support color\n");
            exit(1);
        }
        
        start_color();
        init_pair(1, COLOR_YELLOW, COLOR_BLACK);
        init_pair(2, COLOR_CYAN, COLOR_BLACK);
        init_pair(3, COLOR_WHITE, COLOR_BLACK);
        init_pair(4, COLOR_RED, COLOR_BLACK);
        init_pair(5, COLOR_GREEN, COLOR_BLACK);
        init_pair(6, COLOR_BLUE, COLOR_BLACK);
        init_pair(7, COLOR_CYAN, COLOR_BLACK);
        bkgd(COLOR_PAIR(5) | A_BOLD);

        width = COLS / 2;
        height = LINES /2;

        moveTo();
    }
    
    ~Writer() {
        endwin();
    }

    private:
    void moveTo() {            
        /*    // USE TO GET KEY NUMBERS    
            key = getch();
            printw("I got: %d", key);
            refresh();
            getch();
        */ 
                
        character = 32;
        mvaddch(height, width, character);   
        refresh(); 
        
        auto start = high_resolution_clock::now(); // For random direction 
        auto last_timer = start; // For random direction 
        auto last_timer2 = start; // For random erase character 
        
        bool toggle_erase_character = false;

        while (true) {
            temporary_key = getch();
            // If no key was pressed, randomly choose a direction every 3 seconds.
            auto current_time = high_resolution_clock::now();
            
            if (temporary_key == -1) { // -1 means no key was pressed.
                auto elapsed_time = current_time - last_timer;
                
                random_time = rand() % 5 + 0;
                if( elapsed_time >= std::chrono::seconds(random_time)) { // do your thing every 5 seconds
                    last_timer = current_time; // Reset timer  
                    
           
                    random_direction = rand() % 4 + 1; // Generate a random number between 1 and 4.
                    switch(random_direction) {
                        case 1:
                            if (key == 115) { // If line was drawing down, were turning left so add a left corner.
                                mvaddch(height, width, ACS_LRCORNER);   
                                refresh();                                
                            } else if (key == 119) {//119: UP
                                mvaddch(height, width, ACS_URCORNER);             
                                refresh();  
                            }                            
                            key = 97; //LEFT
                            break;
                        case 2:
                            if (key == 115) { // 115: DOWN
                                mvaddch(height, width, ACS_LLCORNER);  
                                refresh();            
                            } else if (key == 119) { //119: UP
                                mvaddch(height, width, ACS_ULCORNER); 
                                refresh();  
                            }   
                            key = 100; //RIGHT
                            break;
                        case 3:
                            if (key == 97) { // 97: LEFT
                                mvaddch(height, width, ACS_LLCORNER);      
                                refresh();   
                            } else if (key == 100) { // 100: RIGHT
                                mvaddch(height, width, ACS_LRCORNER);   
                                refresh();  
                            }   
                            key = 119; //UP
                            break;
                        case 4:
                            if (key == 97) { // 97: LEFT
                                mvaddch(height, width, ACS_ULCORNER);      
                                refresh();   
                            } else if (key == 100) { // 100: RIGHT
                                mvaddch(height, width, ACS_URCORNER);   
                                refresh();  
                            }                               
                            key = 115; //DOWN
                            break;
                    }
                }
            } else {
                key = temporary_key;     
                last_timer = high_resolution_clock::now(); // Don't fight user for direction, if key was pressed reset timer.
            }
            
            auto elapsed_time2 = current_time - last_timer2;
            if( elapsed_time2 >= std::chrono::seconds(10)) { // do your thing every 5 seconds
                last_timer2 = current_time; // Reset timer  
            
                if (toggle_erase_character == true) {
                    toggle_erase_character = false;
//                     character = ACS_CKBOARD;
//                     mvaddch(height, width, character); 
//                     refresh();
                    color = 4;
//                     continue;
                }
                else {
                    toggle_erase_character = true;
                    character = ACS_CKBOARD;
//                     mvaddch(height, width, character); 
//                     refresh();
                    color = 5;
//                     continue;
                }
            }
            
            if (toggle_erase_character) mvaddch(height, width, 32); // Delete previous character.

            switch(key) {
            case 97: { // LEFT
                width--;
                if (!toggle_erase_character) character = ACS_HLINE;
                if (width == -1) width = COLS;
                    break;
                }
                case 100: { // RIGHT
                    width++;
                    if (!toggle_erase_character) character = ACS_HLINE;
                    if (width == COLS + 1) width = 0;    
                    break;
                }
                case 119: { // UP
                    height--;
                    if (!toggle_erase_character) character = ACS_VLINE;
                    if (height == -1) height = LINES;
                    break;
                }
                case 115: { // DOWN
                    height++;
                    if (!toggle_erase_character) character = ACS_VLINE;
                    if (height == LINES + 1) height = 0;
                    break;
                }
                case 27: { // ESC
                    return;
                }
            }

            attron(COLOR_PAIR(color) | A_BOLD);
            mvaddch(height, width, character);             
            attroff(COLOR_PAIR(color) | A_BOLD);
            refresh();
        }
    }
};

int main(int argc, char** argv)
{    
    Writer();
       
    
    return 0;    
}
