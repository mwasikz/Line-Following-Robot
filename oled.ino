void oled_printXY(int x, int y, String text, bool disp, int size, int color)
{
  oled.setCursor(x, y);
  oled.setTextSize(size);
  oled.setTextColor(color, 1 - color);
  oled.print(text);
  if (disp)oled.display();
}
void oled_print(String text, bool disp, int size, int color)
{
  oled.setTextSize(size);
  oled.setTextColor(color, 1 - color);
  oled.print(text);
  if (disp)oled.display();
}
void oled_println(String text, bool disp, int size, int color)
{
  oled.setTextSize(size);
  oled.setTextColor(color, 1 - color);
  oled.println(text);
  if (disp)oled.display();
}
void oled_printBar(long* a, int l, int r, int x, int y, int h, int max_val)
{
  long v[NUM_SENSORS];
  for (int i = l; i <= r; i++) {
    v[i] = constrain(map(a[i], 0, max_val, 0, 15), 0, 15);
    oled.drawBitmap(x + i * 8, y, bar[v[i]], 8, h, WHITE, BLACK);
  }
}
void oled_printLogo()
{
  
}
void create_bar(int n)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j += 1) {
      if (j >= (n - 1 - i)) {
        bar[i][j] = B01111110;
      }
      else {
        bar[i][j] = B00000000;
      }
    }
  }
}
void create_bar2(int n)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n * 2; j += 2) {
      if (j >= (n * 2 - 1 - i * 2)) {
        bar[i][j] = B01111110;
        bar[i][j + 1] = B01111110;
      }
      else {
        bar[i][j] = B00000000;
        bar[i][j + 1] = B00000000;
      }
    }
  }
}
void oled_drawBitmap(int x, int y, uint8_t *img, int w, int h, int color)
{
  oled.drawBitmap(x, y, img, w, h, color, 1 - color);
  oled.display();
}
void oled_clear(String area, bool disp)
{
  if (area == "y") {
    oled.fillRect(0, 0, 128, 16, BLACK);
  }
  else if (area == "b") {
    oled.fillRect(0, 16, 128, 48, BLACK);
  }
  else {
    oled.clearDisplay();
  }
  if (disp)oled.display();
}
