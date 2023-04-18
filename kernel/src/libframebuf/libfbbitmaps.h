typedef struct
{
    int width;
    int height;
    uint32_t rawdata[];
} bitmap_t;

bitmap_t create_bitmap(uint32_t []);
void draw_bitmap(bitmap_t *bitmap, int x, int y);
void drawbitmap(uint32_t rawdata[], int width, int height, int x, int y);