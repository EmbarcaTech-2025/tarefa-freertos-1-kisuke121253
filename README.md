
# Tarefa: Roteiro de FreeRTOS #1 - EmbarcaTech 2025

Autor: **João Pedro Lacerda Sousa**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasília, 13/06 de 2025

---

Atividade Roteirizada FreeRTOS na BitDogLab

## Descrição

Neste **sistema embarcado**, desenvolvido na **BitDogLab** com FreeRTOS e **linguagem C**, temos:

✅ Uma **tarefa** que controla um **LED RGB**, alternando suas cores (vermelho, verde e azul) de forma **cíclica**.
✅ Uma **tarefa** que controla **dois buzzers**, emitindo bipes periodicamente.
✅ Uma **tarefa** para o **botão A**, que **suspende ou retoma** o **LED RGB**.
✅ Uma **tarefa** para o **botão B**, que **suspende ou retoma** o **buzzer**.

Isso proporciona uma abordagem multitarefa, mostrando como o FreeRTOS consegue gerenciar diferentes responsabilidades de forma **concorrente**.

---

## 🏹 Funcionalidades

* **LED RGB:**

  * Cores alternadas automaticamente a cada 500ms.
  * Suspenso pelo **botão A (pino 5)**.

* **Buzzer:**

  * Emite um **bipe** de 100ms a cada 1s.
  * Suspenso pelo **botão B (pino 6)**.
  * A saída controla **dois buzzers simultaneamente (pinos 21 e 10)**.

---

## ⚙ Hardware utilizado:

| Periférico       | GPIO |
| ---------------- | ---- |
| **LED Vermelho** | 13   |
| **LED Verde**    | 11   |
| **LED Azul**     | 12   |
| **Buzzer 1**     | 21   |
| **Buzzer 2**     | 10   |
| **Botão A**      | 5    |
| **Botão B**      | 6    |

---

## 🛠 Configuração do ambiente e compilação

1. Clone o **FreeRTOS Kernel** para a pasta `FreeRTOS` dentro do seu projeto:

   ```bash
   git clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git FreeRTOS
   ```

2. Garanta que o arquivo de configuração do FreeRTOS esteja presente em:

   ```
   include/FreeRTOSConfig.h
   ```

   Este arquivo deve conter as configurações específicas para o seu projeto, como prioridades, tamanho de pilha, etc.

3. O arquivo principal do projeto é o **blink.c**, que contém o código multitarefa para controle do LED RGB, buzzer e botões.

4. Compile o projeto usando o **pico-sdk** e o FreeRTOS, preferencialmente via **VSCode** com CMake.

---

## 🕹 Como usar:

1. Compile o código (`blink.c`) no VSCode utilizando o FreeRTOS junto ao SDK da Raspberry Pi Pico.
2. Transfira o `.uf2` gerado para a placa **Raspberry Pi Pico (BitDogLab)**.
3. Conecte a placa.
4. Observe o **LED RGB** alternando suas cores automaticamente e o **buzzer** emitindo bipes.
5. Pressione o **botão A (pino 5)** para **suspender/retomar o LED RGB**.
6. Pressione o **botão B (pino 6)** para **suspender/retomar o buzzer**.

---

## 📁 Estrutura do Código

```
.
├── blink.c             # Código fonte principal com FreeRTOS
├── FreeRTOS/           # Kernel FreeRTOS (clonado do GitHub)
├── include/
│   └── FreeRTOSConfig.h # Configurações do FreeRTOS
├── pico-sdk/           # SDK da Raspberry Pi Pico
├── CMakeLists.txt      # Arquivo para compilação com CMake
└── README.md           # Este arquivo
```

---

## 🔹 Tecnologias utilizadas:

* **Linguagem:** C
* **Placa:** Raspberry Pi Pico (BitDogLab)
* **IDE:** Visual Studio Code
* **Framework:** FreeRTOS
* **SDK:** pico-sdk

---

## ⚡ Por que FreeRTOS?

Com o FreeRTOS é possível:

* Executar várias tarefas quase que **simultaneamente**.
* Suspender, retomar e dar prioridades às tarefas facilmente.
* Implementar aplicações embarcadas de forma organizada e robusta.

---

## 📝 Melhorias adicionais (sugestão)

Se desejar, você pode:

* Implementar **interrupts** ao invés de **polling** para detectar o clique de um botão.
* Utilizar **queues** ou **event groups** para sinalizar eventos entre tarefas.
* Implementar **temporizadores de software** para acionar eventos automaticamente.


---

## 📜 Licença
GNU GPL-3.0.
