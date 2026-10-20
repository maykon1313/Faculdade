clear; clc;
try xdel(winsid()); catch end

s = poly(0, 's');

// Planta completa de 6a ordem
num_g = s + 6;
den_g = s^6 + 11*s^5 + 52*s^4 + 142*s^3 + 241*s^2 + 231*s + 90;
G_full = syslin('c', num_g, den_g);

polos_G = roots(den_g);
printf("--- PLANTA COMPLETA (6a ORDEM) ---\n");
printf("Polos da planta:\n"); disp(polos_G);
printf("Ganho estatico DC G(0) = %.6f\n", horner(G_full, 0));

// Item a)

t = 0:0.05:25;
u_degrau = ones(t);
u_rampa  = t;
u_parab  = t.^2;

y_degrau_full = csim(u_degrau, t, G_full);
y_rampa_full  = csim(u_rampa,  t, G_full);
y_parab_full  = csim(u_parab,  t, G_full);

scf(1); clf;
subplot(3,1,1);
plot(t, y_degrau_full, 'b-', 'LineWidth', 2);
xgrid(1);
xtitle("Resposta ao Degrau: u(t) = 1(t) (i=0)", "Tempo (s)", "y(t)");

subplot(3,1,2);
plot(t, y_rampa_full, 'r-', 'LineWidth', 2);
xgrid(1);
xtitle("Resposta a Rampa: u(t) = t (i=1)", "Tempo (s)", "y(t)");

subplot(3,1,3);
plot(t, y_parab_full, 'k-', 'LineWidth', 2);
xgrid(1);
xtitle("Resposta a Parabola: u(t) = t^2 (i=2)", "Tempo (s)", "y(t)");

// Item b)

// 1) Metodo da Realizacao Balanceada (Truncamento de Gramianos)
G_ss = tf2ss(G_full);
hsv = hankelsv(G_ss);
printf("\n--- VALORES SINGULARES DE HANKEL (hankelsv) ---\n");
disp(hsv);

[G_bal, slv] = balreal(G_ss);

// Reducao para ordem 5:
k = 5;
G_red5_bal = syslin('c', G_bal.A(1:k, 1:k), G_bal.B(1:k, :), G_bal.C(:, 1:k), G_bal.D);
// Normalizacao de ganho DC para erro estatico nulo
G_red5_bal = G_red5_bal * (horner(G_full, 0) / horner(ss2tf(G_red5_bal), 0));

// Reducao para ordem 4:
k = 4;
G_red4_bal = syslin('c', G_bal.A(1:k, 1:k), G_bal.B(1:k, :), G_bal.C(:, 1:k), G_bal.D);
G_red4_bal = G_red4_bal * (horner(G_full, 0) / horner(ss2tf(G_red4_bal), 0));

// Reducao para ordem 3:
k = 3;
G_red3_bal = syslin('c', G_bal.A(1:k, 1:k), G_bal.B(1:k, :), G_bal.C(:, 1:k), G_bal.D);
G_red3_bal = G_red3_bal * (horner(G_full, 0) / horner(ss2tf(G_red3_bal), 0));

printf("\nFT Reduzida de 5a ordem (Balanceada):\n"); disp(clean(ss2tf(G_red5_bal)));
printf("\nFT Reduzida de 4a ordem (Balanceada):\n"); disp(clean(ss2tf(G_red4_bal)));
printf("\nFT Reduzida de 3a ordem (Balanceada):\n"); disp(clean(ss2tf(G_red3_bal)));

// 2) Metodo dos Polos Dominantes com Casamento de Derivadas (Aula 9)
// Polos dominantes: p1 = -1, p2,3 = -1 +- j*2 (dominantes Re = -1)
// Em 3a ordem: retem-se {p1, p2, p3}
// g_r3(s) = ( (13/54)*s^2 - (1/3)*s + (1/3) ) / ( (s+1)*(s^2 + 2*s + 5) )
num_dom3 = (13/54)*s^2 - (1/3)*s + (1/3);
den_dom3 = (s + 1)*(s^2 + 2*s + 5);
G_red3_dom = syslin('c', num_dom3, den_dom3);
printf("\nFT Reduzida de 3a ordem (Metodo Aula 9 - Polos Dominantes):\n");
disp(clean(G_red3_dom));

// Item c)

// Simulacoes ao degrau
y5_step = csim(u_degrau, t, G_red5_bal);
y4_step = csim(u_degrau, t, G_red4_bal);
y3_step = csim(u_degrau, t, G_red3_bal);
y3_dom_step = csim(u_degrau, t, G_red3_dom);

scf(2); clf;
plot(t, y_degrau_full, 'k-', 'LineWidth', 2.5);
plot(t, y5_step, 'b--', 'LineWidth', 1.5);
plot(t, y4_step, 'g-.', 'LineWidth', 1.5);
plot(t, y3_step, 'r:', 'LineWidth', 2);
xgrid(1);
xtitle("Exercicio 3(c) - Comparacao ao Degrau: Completo vs Reducoes", "Tempo (s)", "Amplitude");
legend(["Modelo Completo (6a ordem)"; "Reducao 5a ordem"; "Reducao 4a ordem"; "Reducao 3a ordem"]);

// Simulacoes a rampa
y5_ramp = csim(u_rampa, t, G_red5_bal);
y4_ramp = csim(u_rampa, t, G_red4_bal);
y3_ramp = csim(u_rampa, t, G_red3_bal);

scf(3); clf;
plot(t, y_rampa_full, 'k-', 'LineWidth', 2.5);
plot(t, y5_ramp, 'b--', 'LineWidth', 1.5);
plot(t, y4_ramp, 'g-.', 'LineWidth', 1.5);
plot(t, y3_ramp, 'r:', 'LineWidth', 2);
xgrid(1);
xtitle("Exercicio 3(c) - Comparacao a Rampa: Completo vs Reducoes", "Tempo (s)", "Amplitude");
legend(["Modelo Completo (6a ordem)"; "Reducao 5a ordem"; "Reducao 4a ordem"; "Reducao 3a ordem"]);

// Simulacoes a parabola
y5_parab = csim(u_parab, t, G_red5_bal);
y4_parab = csim(u_parab, t, G_red4_bal);
y3_parab = csim(u_parab, t, G_red3_bal);

scf(4); clf;
plot(t, y_parab_full, 'k-', 'LineWidth', 2.5);
plot(t, y5_parab, 'b--', 'LineWidth', 1.5);
plot(t, y4_parab, 'g-.', 'LineWidth', 1.5);
plot(t, y3_parab, 'r:', 'LineWidth', 2);
xgrid(1);
xtitle("Exercicio 3(c) - Comparacao a Parabola: Completo vs Reducoes", "Tempo (s)", "Amplitude");
legend(["Modelo Completo (6a ordem)"; "Reducao 5a ordem"; "Reducao 4a ordem"; "Reducao 3a ordem"]);

printf("\nErros medios quadraticos ao degrau em relacao ao modelo completo:\n");
printf("Erro RMS Ordem 5: %e\n", sqrt(mean((y_degrau_full - y5_step).^2)));
printf("Erro RMS Ordem 4: %e\n", sqrt(mean((y_degrau_full - y4_step).^2)));
printf("Erro RMS Ordem 3 (Balanceada): %e\n", sqrt(mean((y_degrau_full - y3_step).^2)));
printf("Erro RMS Ordem 3 (Polos Dominantes): %e\n", sqrt(mean((y_degrau_full - y3_dom_step).^2)));
