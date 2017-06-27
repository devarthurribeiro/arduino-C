#include <stdlib.h>
#include <windows.h>
#include <stdio.h>

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
  dcb.ByteSize = 7;             // Tamanho de dados, xmit e rcv
  dcb.Parity = EVENPARITY;        // Sem paridade bit
  dcb.StopBits = ONESTOPBIT;    // Um bit de parada
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
  printf("%d\n", op);

  if (op == 1) {
    EnviaComando('a');
    r = RecebeResposta();
  }else{
    return(0);
  }
}

void EnviaComando(char comando){
  TotalBytesaEnviar = 1;
  TxBuff[0] = comando;
  WriteFile(serial, &TxBuff, TotalBytesaEnviar, &BytesEnviados, NULL );
}

char RecebeResposta(void){
    TotalBytesaReceber = 1;
    RxBuff[0] = 0;
    ReadFile(hSerial, &RxBuff, TotalBytesaReceber, &BytesRecebidos, NULL);
    return RxBuff[0];
}
