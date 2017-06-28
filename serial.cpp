#include <stdlib.h>
#include <windows.h>
#include <stdio.h>

HANDLE hSerial;
char TxBuff [12];
char RxBuff [12];

HANDLE serial;
unsigned int TotalBytesaEnviar;
unsigned int TotalBytesaReceber;
unsigned long BytesEnviados;
unsigned long BytesRecebidos = 0;
bool bErrorFlag = false;

void EnviaComando(char comando){
  TotalBytesaEnviar = 1;
  TxBuff[0] = comando;
  bErrorFlag =  WriteFile(serial, &TxBuff, TotalBytesaEnviar, &BytesEnviados, NULL );
  if (bErrorFlag == false){
    printf("Terminal failure: Unable to write to file.\n");
  }
}

char RecebeResposta(void){
    TotalBytesaReceber = 1;
    RxBuff[0] = 0;
    ReadFile(hSerial, &RxBuff, TotalBytesaReceber, &BytesRecebidos, NULL);
    return RxBuff[0];
}

int main() {
  DCB dcb={0};
  HANDLE serial;
  BOOL fSuccess;
  char *pcCommPort = "COM3";

  COMMTIMEOUTS timeouts={0};
  timeouts.ReadIntervalTimeout=50;
  timeouts.ReadTotalTimeoutConstant=50;
  timeouts.ReadTotalTimeoutMultiplier=10;
  timeouts.WriteTotalTimeoutConstant=50;
  timeouts.WriteTotalTimeoutMultiplier=10;


  serial = CreateFile( pcCommPort,
    GENERIC_READ | GENERIC_WRITE,
    FILE_SHARE_READ,
    NULL,
    OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL,
    NULL
  );

  if (serial == INVALID_HANDLE_VALUE)
  {
    printf ("Erro na funcao CreateFile %d.\n", GetLastError());
    return (1);
  }

  if(!SetCommTimeouts(serial, &timeouts))
  {
    printf("Ocorreu um erro\n");
  }

  fSuccess = GetCommState(serial, &dcb);

  if (!fSuccess)
  {
    printf ("Erro na funcao GetCommState %d.\n", GetLastError());
    return (2);
  }


  dcb.BaudRate = 9600;     // Definir a taxa de transmissão
  dcb.ByteSize = 8;             // Tamanho de dados, xmit e rcv
  dcb.Parity = EVENPARITY;        // Sem paridade bit
  dcb.StopBits = NOPARITY;    // Um bit de parada
  fSuccess = SetCommState(serial, &dcb);

  if (!fSuccess)
  {
    printf ("Erro na funcao SetCommState. Error: %d.\n", GetLastError());
    return (3);
  }

  printf ("Porta serial %s configurada com sucesso.\n", pcCommPort);

  puts("_____________________________________________\n");
  int op = 0;

  puts("MENU:");
  puts("1 - ATIVAR PORTA");
  puts("2 - SAIR");
  scanf("%d", &op);
  if (op == 1) {
    EnviaComando('a');
    char r = RecebeResposta();
    printf("resposta: %s\n", &r);
  }else{
    return(0);
  }
}
