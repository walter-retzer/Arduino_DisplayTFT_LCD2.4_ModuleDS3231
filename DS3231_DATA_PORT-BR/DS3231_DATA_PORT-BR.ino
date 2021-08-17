
/**********************************************************************************************************************
    AUTOR: WALTER DAWID RETZER
    
    PROJETO: DISPLAY LCD TFT 2.4" E MÓDULO DS3231      
    VERSÃO: 1.01
    DATA: 17/08/2021
    ARQUIVOS ANEXO: BIBLIOTECA DS3231 ALTERADA PARA EXIBIR AS DATAS EM PORTUGUÊS-BR 
                    SKETCH DO PROGRAMA PARA EXIBIÇÃO DA DATA E HORÁRIO UTILIZANDO DISPLAY TFT LCD 2.4"
  
-----------------------------------------------------------------------------------------------------------------------
  COMENTÁRIOS:     

  - DEMONSTRAÇÃO DAS FUNÇÕES DE EXIBIÇÃO DE DATA EM PORTUGUÊS-Br E HORÁRIO DO MÓDULO DS3231.

-----------------------------------------------------------------------------------------------------------------------                  
  MATERIAL PARA O PROJETO:

  - ARDUINO MEGA
  - MÓDULO DS3231
  - DISPLAY TFT 2.4" (DRIVER: ILI9341)
  - JUMPERS PARA A CONEXÃO
  
-----------------------------------------------------------------------------------------------------------------------
  CONEXÃO DO MÓDULO DS3231 E ARDUINO MEGA:
          
  Módulo DS3231 pino  SDA  ->  Arduino Mega Digital 20 (SDA)
  Módulo DS3231 pino  SCL  ->  Arduino Mega Digital 21 (SCL)
  Módulo DS3231 pino  VCC  ->  Arduino Mega 5V
  Módulo DS3231 pino  GND  ->  Arduino Mega GND
-----------------------------------------------------------------------------------------------------------------------
  PRINCIPAIS FUNÇÕES DO MÓDULO DS3231:
  
  rtc.getTimeStr()                EXIBE O HORÁRIO NO FORMATO: HH:MM:SS
  rtc.getDOWStr()                 EXIBE O NOME DO DIA DA SEMANA: "Segunda-Feira"
  rtc.getMonthStr()               EXIBE O NOME DO MÊS: "Janeiro"
  rtc.getDOWStr(FORMAT_SHORT);    EXIBE O NOME DO DIA DA SEMANA ABREVIADO: "Seg"
  rtc.getTimeStr(FORMAT_SHORT);   EXIBE O HORÁRIO NO FORMATO: HH:MM
  rtc.getMonthStr(FORMAT_SHORT)   EXIBE O NOME DO MÊS ABREVIADO: "Jan"

  char const divider = '/';
  rtc.getDateStr(FORMAT_LONG, FORMAT_LITTLEENDIAN, divider)   EXIBE A DATA NO FORMATO: DIA/MÊS/ANO  -- DD/MM/YYYY
  rtc.getDateStr(FORMAT_SHORT, FORMAT_LITTLEENDIAN, divider)  EXIBE A DATA NO FORMATO: DIA/MÊS/ANO  -- DD/MM/YY
 
-----------------------------------------------------------------------------------------------------------------------                
**********************************************************************************************************************/

// ========================================================================================================
// INCLUSÃO DAS BIBLIOTECAS QUE SERÃO UTILIZADAS NO PROJETO:
#include <MCUFRIEND_kbv.h>  //BIBLIOTECA DO DISPLAY TFT LCD 2.4"
MCUFRIEND_kbv tft;  //DECLARAÇÃO DO NOME DO DISPLAY TFT LCD 2.4"

#include <DS3231.h>  //BIBLIOTECA DO MÓDULO DS3231
#include <Wire.h> //BIBLIOTECA PARA COMUNICAÇÃO ENTRE DISPOSITIVOS I2C

// ========================================================================================================
// DECLARAÇÃO DAS VARIÁVEIS QUE SERÃO UTILIZADAS NO PROJETO:

DS3231  rtc(SDA, SCL);  //DECLARANDO O NOME DA VARIAVEL PARA RECEBER AS INFORMAÇÕES DO MÓDULO DS3231;
Time  t;  //DECLARAÇÃO DA VARIÁVEL t 

String data;
String dataatual;
String diadasemana;
String diadasemanaatual = " ";

unsigned long atualiza_lcd; //variável auxiliar para atualizar o display

// ========================================================================================================
// DECLARAÇÃO DA FUNÇÃO QUE EXIBE A DATA E HORÁRIO NO DISPLAY:

void data_hora();

// ========================================================================================================
// DEFINIÇÃO DAS CORES NO DISPLAY TFT:

#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF
#define GREY            0x8410
#define ORANGE2         0xE880
#define ORANGE1         0xE800
#define ORANGE          0xFD20
#define GREENYELLOW     0xAFE5
#define LIGHTGREY       0xC618
#define DARKGREY        0x7BEF
#define OLIVE           0x7BE0
#define DARKGREEN       0x03E0
#define DARKCYAN        0x03EF
#define MARROM          0x7800
#define PURPLE          0x780F



//========================================================================================================
// FUNÇÃO SETUP:


void setup () {

//========================================================================================================
// INICIANDO DISPLAY LCD TFT 2.4":

    uint16_t ID = tft.readID(); 
    tft.begin(ID);
    tft.setRotation(0);
    tft.fillScreen(BLACK);
    delay(1000);
    
    tft.fillRoundRect(20, 40, 200, 210, 15, RED);
    tft.drawRoundRect(20, 40, 200, 210, 15, WHITE);
  
    delay(1500);

    tft.setCursor(32,120);
    tft.setTextColor(WHITE);
    tft.setTextSize(6);
    tft.print(F("TESTE"));
    
    delay(1500);

    tft.fillRect(0, 0, 240, 320, BLACK);
     
    delay(1000);
    
// ========================================================================================================
// INICIALIZAÇÃO DO MÓDULO DS3231:

    rtc.begin();
    
// ========================================================================================================
// CONFIGURAÇÃO PARA A GRAVAÇÃO DA DATA E HORA AO MÓDULO DS3231: 
// APÓS O PRIMEIRO DOWNLOAD, DEVE-SE COMENTAR AS 3 LINHAS ABAIXO, ESSAS FUNÇÕES SÃO PARA CONFIGURAR A HORA ATUAL AO MÓDULO.
// DEPOIS DE COMENTADAS ESSAS 3 LINHAS, DEVE-SE EXECUTAR NOVO DOWNLOAD AO ARDUINO, PARA ASSIM O MÓDULO EXECUTAR CORRETAMENTE
/*
    rtc.setDOW(SEGUNDA);     // Setar o dia da Semana: DOMINGO / SEGUNDA / TERCA / QUARTA / QUINTA / SEXTA / SABADO
    rtc.setTime(23,45,00);   // Setar o horário para: 14:00:00 (24hr formato)
    rtc.setDate(16,8,2021);  // Setar a data para 20 de Julho de 2021
*/
    t = rtc.getTime(); 
  
    tft.setTextColor(YELLOW, BLACK);
    tft.setCursor(8, 10);
    tft.setTextSize(2);
    tft.print(F("TESTE DS3231 E TFT:")); 
    delay(1000);
    
// ========================================================================================================
// SETUP DOS DESENHOS DOS QUADROS VERMELHOS, ONDE SERÃO EXIBIDOS AS INFORMAÇÕES:
 
    char const divider = '/';
    dataatual = rtc.getDateStr(FORMAT_LONG, FORMAT_LITTLEENDIAN, divider);
  
    tft.fillRect(0, 30, 240, 40, RED);
    tft.fillRect(0, 80, 240, 40, RED);
    tft.fillRect(0, 130, 240, 40, RED);
    tft.fillRect(0, 180, 240, 40, RED);
    tft.fillRect(0, 230, 240, 40, RED);
    tft.fillRect(0, 280, 240, 40, RED);
    
    atualiza_lcd = millis();
}




//========================================================================================================
// FUNÇÃO LOOP: ATUALIZA TELA, A CADA 1 SEGUNDO

void loop()
{
  if (millis() - atualiza_lcd >= 1000){
    atualiza_lcd = millis();
    data_hora();
    
  } 
}





//======================================================================================================== 
// FUNÇÃO PARA EXIBIR A DATA E HORA:

void data_hora() {

  String data1;
  String data2;
  String hora1;
  String hora;

  t = rtc.getTime();
   
// ========================================================================================================
// EXIBIÇÃO DA DATA E HORÁRIO:

  hora = rtc.getTimeStr();
  tft.setCursor(55, 40);
  tft.setTextColor(WHITE, RED);
  tft.setTextSize(3);
  tft.print(hora); 

// ========================================================================================================
// EXIBIÇÃO DA DATA:
  char const divider = '/';
  data = rtc.getDateStr(FORMAT_LONG, FORMAT_LITTLEENDIAN, divider);

// TESTA SE HOUVE MUDANÇA NA DATA, CASO HAJA, ATUALIZA A DATA NO DISPLAY:
  if(dataatual != data){
      tft.setCursor(35,90);
      tft.setTextSize(3);
      tft.setTextColor(WHITE, RED);
      tft.print(data);  
      dataatual = data;
  } else{
      tft.setCursor(35, 90);
      tft.setTextSize(3);
      tft.setTextColor(WHITE, RED);
      dataatual = rtc.getDateStr(FORMAT_LONG, FORMAT_LITTLEENDIAN, divider);
      tft.print(dataatual);
  }

// ========================================================================================================
// EXIBIÇÃO DO DIA DA SEMANA:

  String diadasemana = rtc.getDOWStr();
  String seg = "Segunda-Feira";
  String ter = "Terca-Feira";
  String qua = "Quarta-Feira";
  String qui = "Quinta-Feira";
  String sex = "Sexta-Feira";
  String sab = "Sabado";
  String dom = "Domingo";

  if (diadasemanaatual != diadasemana){
      
      if (seg.equals(diadasemana)){
        tft.fillRect(0, 130, 240, 40, RED);
        tft.setTextColor(WHITE, RED);
        tft.setCursor(15,140);
        tft.setTextSize(2);
        tft.print(F("DIA: "));
        tft.print(rtc.getDOWStr());
        diadasemanaatual = diadasemana;
      } 
    
      else if (ter.equals(diadasemana)){
            tft.fillRect(0, 130, 240, 40, RED);
            tft.setTextColor(WHITE, RED);
            tft.setCursor(30,140);
            tft.setTextSize(2);
            tft.print(F("DIA: "));
            tft.print(rtc.getDOWStr());
            diadasemanaatual = diadasemana;
      } 
    
      else if (qua.equals(diadasemana)){
            tft.fillRect(0, 130, 240, 40, RED);
            tft.setTextColor(WHITE, RED);
            tft.setCursor(20,140);
            tft.setTextSize(2);
            tft.print(F("DIA: "));
            tft.print(rtc.getDOWStr());
            diadasemanaatual = diadasemana;
      } 
        
      else if (qui.equals(diadasemana)){
            tft.fillRect(0, 130, 240, 40, RED);
            tft.setTextColor(WHITE, RED);
            tft.setCursor(20,140);
            tft.setTextSize(2);
            tft.print(F("DIA: "));
            tft.print(rtc.getDOWStr());
            diadasemanaatual = diadasemana;
      } 
    
      else if (sex.equals(diadasemana)){
            tft.fillRect(0, 130, 240, 40, RED);
            tft.setTextColor(WHITE, RED);
            tft.setCursor(28,140);
            tft.setTextSize(2);
            tft.print(F("DIA: "));
            tft.print(rtc.getDOWStr());
            diadasemanaatual = diadasemana;
      } 
    
      else if (sab.equals(diadasemana)){
            tft.fillRect(0, 130, 240, 40, RED);
            tft.setTextColor(WHITE, RED);
            tft.setCursor(55,140);
            tft.setTextSize(2);
            tft.print(F("DIA: "));
            tft.print(rtc.getDOWStr());
            diadasemanaatual = diadasemana;
      } 
    
      else if (dom.equals(diadasemana)){
            tft.fillRect(0, 130, 240, 40, RED);
            tft.setTextColor(WHITE, RED);
            tft.setCursor(50,140);
            tft.setTextSize(2);
            tft.print(F("DIA: "));
            tft.print(rtc.getDOWStr());
            diadasemanaatual = diadasemana;
      }
      
    }

    // ========================================================================================================
    // EXIBIÇÃO DO MÊS:
    
    tft.setTextColor(WHITE, RED);
    tft.setCursor(50,190);
    tft.setTextSize(2);
    tft.print(F("MES: "));
    tft.print(rtc.getMonthStr());
    
    // ========================================================================================================
    // EXIBIÇÃO DO MÊS ABREVIADO/ANOYYYY:
    
    tft.setTextColor(WHITE, RED);
    tft.setCursor(80,240);
    tft.setTextSize(2);
    tft.print(rtc.getMonthStr(FORMAT_SHORT));
    tft.print("/");
    tft.print(t.year, DEC);  
   
    // ========================================================================================================
    // EXIBIÇÃO DA DATA E HORÁRIO:
    
    tft.setTextColor(WHITE, RED);
    tft.setCursor(8,290);
    tft.setTextSize(2);
    
    // ========================================================================================================
    // EXIBIÇÃO DA DATA DD/MM/YY:
    
    data1 = rtc.getDateStr(FORMAT_SHORT, FORMAT_LITTLEENDIAN, divider);
    tft.print(data1);

    // ========================================================================================================
    // EXIBIÇÃO DO DIA DA SEMANA ABREVIADO: 
    
    data2 = rtc.getDOWStr(FORMAT_SHORT);
    tft.setCursor(118,290);
    tft.print(data2);

    // ========================================================================================================
    // EXIBIÇÃO DO HORÁRIO HH:MM 
    
    hora1 = rtc.getTimeStr(FORMAT_SHORT);
    tft.setCursor(163,290);
    tft.print(hora1);
    tft.print(F("h"));

}
