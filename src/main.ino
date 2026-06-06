#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>


const char plan5[] = "Update core modules, fix bugs, deploy to server.";
const char plan6[] = "Update core logic, fix bugs, deploy to cloud.";

// تنظیمات قطعات
LiquidCrystal_I2C lcd(0x27, 16, 2); 
Servo myServo;

// الگوریتم بهینه LCS برای رم محدود میکروکنترلر
// استفاده از تکنیک Space Optimization با پیچیدگی فضایی O(n)
int calculateLCS(const char* X, const char* Y, int m, int n) {
  int L[2][n + 1];
  bool bi; // متغیری برای سوئیچ بین دو سطر ماتریس

  for (int i = 0; i <= m; i++) {
    bi = i & 1; // استفاده از عملگر بیتی برای سرعت بیشتر (معادل i % 2)
    for (int j = 0; j <= n; j++) {
      if (i == 0 || j == 0)
        L[bi][j] = 0;
      else if (X[i - 1] == Y[j - 1])
        L[bi][j] = L[1 - bi][j - 1] + 1;
      else
        L[bi][j] = max(L[1 - bi][j], L[bi][j - 1]);
    }
  }
  return L[bi][n];
}

void setup() {
  Serial.begin(9600);
  
  // راه‌اندازی نمایشگر
  lcd.init();
  lcd.backlight();
  
  // راه‌اندازی موتور سروو (پین 9)
  myServo.attach(9);
  myServo.write(0); // وضعیت اولیه: موتور در زاویه صفر

  int m = strlen(plan5);
  int n = strlen(plan6);

  lcd.setCursor(0, 0);
  lcd.print("Analyzing Diff..");

  // محاسبه طول بزرگترین زیردنباله مشترک
  int lcsLength = calculateLCS(plan5, plan6, m, n);
  
  // محاسبه درصد شباهت دو متن
  int maxLength = max(m, n);
  float similarity = ((float)lcsLength / maxLength) * 100.0;

  delay(1500); // مکث برای دیده شدن پیام اولیه
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Match: ");
  lcd.print(similarity);
  lcd.print("%");

  Serial.print("LCS Length: ");
  Serial.println(lcsLength);
  Serial.print("Similarity: ");
  Serial.print(similarity);
  Serial.println("%");

  // منطق مکاترونیکی: اگر تفاوت متن‌ها زیاد بود (شباهت کمتر از 85%)، سیستم واکنش فیزیکی نشان دهد
  if (similarity < 85.0) {
    lcd.setCursor(0, 1);
    lcd.print("Diff High! Lock.");
    myServo.write(90); // چرخش موتور به نشانه قفل کردن یا هشدار
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Plans Matched.");
    myServo.write(0);
  }
}

void loop() {
  // سیستم پس از یک بار تحلیل عمیق متوقف می‌شود تا منابع هدر نرود
}
