clear; clc;
try xdel(winsid()); catch end

q  = 0.1;
C1 = 1.5;
C2 = 0.8;
R1 = 2.0;
R2 = 3.0;

Req = (R1 * R2) / (R1 + R2); // 6 / 5 = 1.2 s/m^2

// Item a)

A = [-1/(R1*C1),  1/(R1*C1); ...
      1/(R1*C2), -1/(Req*C2)];
B = [1/C1; 0];
C = eye(2,2);
D = [0; 0];

polos = spec(A);
wn = sqrt(det(A));
zeta = -trace(A) / (2 * wn);

printf("Matriz A:\n"); disp(A);
printf("Polos do sistema (autovalores de A):\n"); disp(polos);
printf("Frequencia natural nao-amortecida: wn = %.6f rad/s\n", wn);
printf("Fator de amortecimento: zeta = %.6f\n", zeta);

if zeta > 1.0 then
    printf("Como zeta = %.4f > 1 (polos reais, distintos e negativos), o sistema e SOBREAMORTECIDO.\n", zeta);
elseif abs(zeta - 1.0) < 1e-4 then
    printf("Como zeta = 1.0, o sistema e CRITICAMENTE AMORTECIDO.\n");
else
    printf("Como 0 < zeta < 1.0, o sistema e SUBAMORTECIDO.\n");
end

sys_tanques = syslin('c', A, B, C, D);
t = 0:0.1:40;
u = q * ones(t); // Entrada de vazao constante q = 0.1 m^3/s

h = csim(u, t, sys_tanques);
h1 = h(1, :);
h2 = h(2, :);

// Item c)

delta_h = h1 - h2;
q1 = delta_h / R1;
q2 = h2 / R2;

// Grafico 1: Alturas h1, h2 e diferenca delta_h
scf(1); clf;
plot(t, h1, 'b-', 'LineWidth', 2);
plot(t, h2, 'r--', 'LineWidth', 2);
plot(t, delta_h, 'k-.', 'LineWidth', 2);
xgrid(1);
xtitle("Exercicio 2(c) - Alturas dos Niveis e Diferenca (delta_h = h1 - h2)", "Tempo (s)", "Nivel (m)");
legend(["h_1(t)"; "h_2(t)"; "delta_h(t) = h_1(t) - h_2(t)"]);

// Grafico 2: Vazoes q1 e q2
scf(2); clf;
plot(t, q1, 'b-', 'LineWidth', 2);
plot(t, q2, 'r--', 'LineWidth', 2);
plot(t, u, 'k:', 'LineWidth', 1.5);
xgrid(1);
xtitle("Exercicio 2(c) - Vazoes q_1(t), q_2(t) e Entrada q", "Tempo (s)", "Vazao (m^3/s)");
legend(["q_1(t) = (h_1 - h_2)/R_1"; "q_2(t) = h_2/R_2"; "q (Entrada constante = 0.1 m^3/s)"]);

// Item d)

lado_esq = u - q2;

h1_dot = (u - q1) / C1;
h2_dot = (q1 - q2) / C2;
lado_dir = C1 * h1_dot + C2 * h2_dot;

erro_balanco = abs(lado_esq - lado_dir);
printf("Erro maximo absoluto na igualdade q - q2 = C1*h1_dot + C2*h2_dot: %e\n", max(erro_balanco));

scf(3); clf;
plot(t, lado_esq, 'b-', 'LineWidth', 2);
plot(t, lado_dir, 'r--', 'LineWidth', 2);
xgrid(1);
xtitle("Exercicio 2(d) - Verificacao: q - q_2 vs (C_1*h1_dot + C_2*h2_dot)", "Tempo (s)", "Taxa Volumetrica (m^3/s)");
legend(["Lado Esquerdo: q - q_2"; "Lado Direito: C_1*h1_dot + C_2*h2_dot"]);

printf("Valores de Regime Permanente (t -> infinito):\n");
printf("h1(inf) = %.4f m  (esperado: %.4f m)\n", h1($), (R1+R2)*q);
printf("h2(inf) = %.4f m  (esperado: %.4f m)\n", h2($), R2*q);
printf("delta_h(inf) = %.4f m  (esperado: %.4f m)\n", delta_h($), R1*q);
printf("q1(inf) = %.4f m^3/s  (esperado: %.4f m^3/s)\n", q1($), q);
printf("q2(inf) = %.4f m^3/s  (esperado: %.4f m^3/s)\n", q2($), q);
