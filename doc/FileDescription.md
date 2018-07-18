typedef struct {
    struct {
        uint8_t df : 3;     //  file table
        uint8_t it : 5;     //  inode table
    } events;
    struct {
        uint8_t df : 3;
        uint8_t it : 5;
    } revents;
} FileDescription;
