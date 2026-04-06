#include "display.h"

#define CHUNK 256

static uint8_t buffer[CHUNK];

//Sending Command Byte to Display
static void write_command(uint8_t cmd){
    gpio_put(CS_PIN,0);
    gpio_put(DC_PIN, 0);
    spi_write_blocking(spi0, &cmd, 1);
    gpio_put(CS_PIN, 1);
}

//Writing Data to display takes in array of data
static void write_data(const uint8_t *data, size_t len){
   if (len == 0 || data == NULL){
    return;
   }
    gpio_put(CS_PIN,0);
    gpio_put(DC_PIN,1);
    
    spi_write_blocking(spi0, data, len);

    gpio_put(CS_PIN,1);
}

//Combines write_data and write_command
static void write_command_data(uint8_t cmd, const uint8_t *data, size_t len){
    gpio_put(CS_PIN,0);
    gpio_put(DC_PIN,0);
    spi_write_blocking(spi0, &cmd, 1);

    gpio_put(DC_PIN,1);
    spi_write_blocking(spi0, data, len);
    
    gpio_put(CS_PIN,1);
}

//returns high bits of a Value
static uint8_t high_bits(int Value){
    return ((Value >> 8) & 0xFF);
}

//returns low bits of a Value
static uint8_t low_bits(int Value){
    return (Value & 0xFF);
}

//Tells display where data is going to be sent
static void set_address_window(int x0, int x1, int y0,int y1){

    if ((x0 > x1) || (y0 > y1) ){
        return;
    }

    uint8_t x0_lo = low_bits(x0);
    uint8_t x0_hi = high_bits(x0);
    uint8_t x1_lo = low_bits(x1);
    uint8_t x1_hi = high_bits(x1);

    uint8_t xbuf[4] = {x0_hi, x0_lo, x1_hi, x1_lo};

    write_command_data(0x2A, xbuf, 4);

    uint8_t y0_lo = low_bits(y0);
    uint8_t y0_hi = high_bits(y0);
    uint8_t y1_lo = low_bits(y1);
    uint8_t y1_hi = high_bits(y1);

    uint8_t ybuf[4] = {y0_hi, y0_lo, y1_hi, y1_lo};

    write_command_data(0x2B, ybuf, 4);
}

//Drawing a rectangle at a given location
//The x and y are cordinates and the width extends to the left and height extends downwards
void fill_rect(int x, int y, int w, int h, int color){
    if (x < 0){
        w = w - (-1 * x);
        x = 0;
    }
    if (y < 0){
        h = h - (-1 * y);
        y = 0;
    }
    if (x + w > LCD_W){
        w = LCD_W - x;
    }
    if (y + h > LCD_H){
        h = LCD_H - y;
    }

    if ((w <= 0) || (h <= 0)){
        return;
    }


    int x1 = x + w - 1;
    int y1 = y + h - 1;
    set_address_window(x, x1, y, y1);

    for (int i = 0; i < CHUNK; i+=2){
        buffer[i] = high_bits(color);
        buffer[i+1] = low_bits(color);
    }

    write_command(0x2C);
    int total_bytes = w * h * 2;
    while(total_bytes > 0){
        int to_send = CHUNK < total_bytes ? CHUNK : total_bytes;
        write_data(buffer, to_send);
        total_bytes -= to_send;
    }
}

void draw_pixel(int x, int y, int color){
    fill_rect(x, y, 1, 1, color);
}
//Fills whole display with specific color
void display_fill(int color){
    fill_rect(0, 0, LCD_W, LCD_H, color);
}

//Draws the Net Line with specific paramaters to change aesthetic
void net_line(int rectangle_width, int rectangle_height, int color){
    for (int i = 0; i <= LCD_H; i += rectangle_height + 10){
        fill_rect((LCD_W/2), i,  rectangle_width, rectangle_height, color);
    }
}

//Initializing the display and Pins on Pico
void display_init(void){
    //1 MHZ
     spi_init(spi0, 10 * 1000 * 1000);

    gpio_set_function(18,GPIO_FUNC_SPI);
    gpio_set_function(19, GPIO_FUNC_SPI);

    spi_set_format(spi0, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

    gpio_init(CS_PIN);
    gpio_set_dir(CS_PIN,GPIO_OUT);
    gpio_put(CS_PIN,1);

    gpio_init(DC_PIN);
    gpio_set_dir(DC_PIN,GPIO_OUT);
    gpio_put(DC_PIN,1);

    gpio_init(RST_PIN);
    gpio_set_dir(RST_PIN, GPIO_OUT);

    //Button Initialization
    gpio_init(LEFT_A_PIN);
    gpio_set_dir(LEFT_A_PIN, GPIO_IN);
    gpio_pull_up(LEFT_A_PIN);

    gpio_init(LEFT_B_PIN);
    gpio_set_dir(LEFT_B_PIN, GPIO_IN);
    gpio_pull_up(LEFT_B_PIN);

    gpio_init(RIGHT_A_PIN);
    gpio_set_dir(RIGHT_A_PIN, GPIO_IN);
    gpio_pull_up(RIGHT_A_PIN);

    gpio_init(RIGHT_B_PIN);
    gpio_set_dir(RIGHT_B_PIN, GPIO_IN);
    gpio_pull_up(RIGHT_B_PIN);

    //Reseting screen
    gpio_put(RST_PIN,1);
    gpio_put(RST_PIN,0);
    sleep_ms(50);
    gpio_put(RST_PIN,1);
    sleep_ms(120);

    write_command(0x01);
    sleep_ms(50);
    write_command(0x11);
    sleep_ms(120);

    //MADCTL COMMAND
    uint8_t val[1] = {0x28};
    write_command_data(0x36, val, 1);
    write_command(0x29);
    sleep_ms(50);

    uint8_t pixel_format_buf[1] = {0x55};
    write_command_data(0x3A, pixel_format_buf, 1);
}
