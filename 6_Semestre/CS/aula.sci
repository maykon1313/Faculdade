// Limpeza de ambiente
clear; clc;

// Define a variável complexa de Laplace
s = poly(0, 's');

// 1. Definição da Planta e do Compensador
G = 1.06 / (s * (s + 1) * (s + 2));              // Planta original
C = 0.9656 * (s + 0.05) / (s + 0.005);            // Compensador de Atraso

// 2. Malha Aberta e Malha Fechada
L_sem = G;                                        // Sem compensação
L_com = C * G;                                    // Com compensação

T_sem = syslin('c', L_sem / (1 + L_sem));         // MF sem compensador
T_com = syslin('c', L_com / (1 + L_com));         // MF com compensador

// 3. Simulação 1: Resposta ao Degrau
t = 0:0.1:40;
y_degrau_sem = csim('step', t, T_sem);
y_degrau_com = csim('step', t, T_com);

figure(1);
plot(t, y_degrau_sem, 'b', t, y_degrau_com, 'r');
xtitle('Resposta ao Degrau', 'Tempo (s)', 'Amplitude');
legend(['Sem compensador', 'Com compensador']);
xgrid();

// 4. Simulação 2: Resposta à Rampa (Erro de Velocidade)
u_rampa = t;                                      // Entrada tipo rampa u(t) = t
y_rampa_sem = csim(u_rampa, t, T_sem);
y_rampa_com = csim(u_rampa, t, T_com);

figure(2);
plot(t, u_rampa, 'k--', t, y_rampa_sem, 'b', t, y_rampa_com, 'r');
xtitle('Resposta à Rampa (Análise do Erro de Velocidade)', 'Tempo (s)', 'Amplitude');
legend(['Entrada (Rampa)', 'Sem compensador', 'Com compensador']);
xgrid();

// 5. Simulação 3: Lugar das Raízes (Root Locus)
figure(3);
evans(syslin('c', L_com));
xtitle('Lugar das Raízes do Sistema Compensado');
