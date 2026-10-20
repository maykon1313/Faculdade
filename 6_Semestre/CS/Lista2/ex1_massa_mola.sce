clear; clc;
try xdel(winsid()); catch end

m = 400;
k = 100;

// Item a)

wn = sqrt(k/m);
printf("Frequencia natural nao-amortecida: wn = %.4f rad/s\n", wn);
printf("Faixa de amortecimento valida: 160 < b < 320 N.s/m\n");

zeta_escolhido = 0.6;
b = 2 * m * wn * zeta_escolhido;
printf("Valor de b escolhido (para zeta = %.2f): b = %.2f N.s/m\n", zeta_escolhido, b);

// Item b)

A = [0, 1; -(k/m), -(b/m)];
B = [b/m; (k/m) - (b/m)^2];
C = eye(2,2);
D = [0; 0];

sys_estados = syslin('c', A, B, C, D);


t = 0:0.05:35;
x = csim('step', t, sys_estados);

x1 = x(1, :);
x2 = x(2, :);

scf(1); clf;
plot(t, x1, 'b-', 'LineWidth', 2);
plot(t, x2, 'r--', 'LineWidth', 2);
xgrid(1);
xtitle("Exercicio 1(b) - Comportamento das Variaveis de Estado x1 e x2", "Tempo (s)", "Amplitude");
legend(["x_1(t) = Posicao y(t)"; "x_2(t) = y_dot(t) - (b/m)*u(t)"]);

// Item c)

u_degrau = ones(t);
v = x2 + (b/m) * u_degrau;

scf(2); clf;
plot(t, v, 'k-', 'LineWidth', 2);
xgrid(1);
xtitle("Exercicio 1(c) - Velocidade do Bloco de Massa m: v(t) = x_2(t) + (b/m)*u(t)", "Tempo (s)", "Velocidade (m/s)");
legend(["v(t) = y_dot(t)"]);

printf("Regime permanente x1(inf) = %.4f m\n", x1($));
printf("Regime permanente x2(inf) = %.4f\n", x2($));
printf("Regime permanente v(inf) = %.4f m/s\n", v($));
