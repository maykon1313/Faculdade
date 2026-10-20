clear; clc;
try xdel(winsid()); catch end

s = poly(0, 's');

num4 = 1;
den4 = s^6 + 48*s^5 + 817*s^4 + 5720*s^3 + 15075*s^2 + 27000*s + 16875;
G_full = syslin('c', num4, den4);

polos_G4 = roots(den4);
printf("--- PLANTA COMPLETA ---\n");
printf("Polos da planta:\n"); disp(polos_G4);

// Item c)
den4_r = (s + 1) * (s^2 + 2*s + 5);
num4_r = 1 / 3375;
G_red = syslin('c', num4_r, den4_r);

printf("\n--- PLANTA REDUZIDA (Item c) ---\n");
printf("Denominador reduzido: D_r(s) = (s+1)(s^2 + 2s + 5) = s^3 + 3s^2 + 7s + 5\n");
printf("Numerador reduzido: N_r = 1/3375 = %.8f\n", num4_r);
printf("Ganho DC G_full(0) = %.8f | G_red(0) = %.8f (Identicos!)\n", horner(G_full, 0), horner(G_red, 0));

sd = -4 + 3*%i;
printf("\nPolos dominantes de malha fechada escolhidos: sd = -4 +- j3\n");
printf("sigma = 4.0 (> 3), zeta = 0.8, beta = 36.87 graus (< 40 graus)\n");

// Item a)
d1 = 85;
d0 = 2803;
n3 = 44191 * 3375;
n2 = 455954 * 3375;
n1 = 2065985 * 3375;
n0 = 4000000 * 3375;

Dc_diof = s * (s^2 + d1*s + d0);
Nc_diof = n3*s^3 + n2*s^2 + n1*s + n0;
C_diof = syslin('c', Nc_diof, Dc_diof);

printf("\nCompensador Diofantino C_diof(s):\n");
disp(clean(C_diof));

// Item d)
zc_d1 = 1.0;
zc_d2 = 2.5;
pc_d  = 18.0;

G_open_d = syslin('c', (s + zc_d1)*(s + zc_d2)*num4_r, s*(s + pc_d)*den4_r);
// Cálculo do ganho Kc pelo critério de magnitude em sd = -4 + 3j
Kc_d = 1 / abs(horner(G_open_d, sd));
C_lr_red = syslin('c', Kc_d * (s + zc_d1) * (s + zc_d2), s * (s + pc_d));

printf("\nCompensador LR na Planta Reduzida C_lr_red(s):\n");
printf("Ganho Kc_d = %.2f\n", Kc_d);
disp(clean(C_lr_red));

// Item b)
zc_b1 = 1.0;
zc_b2 = 2.0;
pc_b  = 25.0;

G_open_b = syslin('c', (s + zc_b1)*(s + zc_b2)*num4, s*(s + pc_b)*den4);
Kc_b = 1 / abs(horner(G_open_b, sd));
C_lr_full = syslin('c', Kc_b * (s + zc_b1) * (s + zc_b2), s * (s + pc_b));

printf("\nCompensador LR na Planta Completa C_lr_full(s):\n");
printf("Ganho Kc_b = %.2f\n", Kc_b);
disp(clean(C_lr_full));

// Imagem 1: Lugar das Raízes da Planta Completa
scf(1); clf;
evans(clean(G_open_b), 500000);
xgrid(1);
xtitle("Lugar das Raízes - Planta Completa Compensada", "Eixo Real", "Eixo Imaginário");

// Imagem 2: Lugar das Raízes da Planta Reduzida
scf(2); clf;
evans(clean(G_open_d), 500000);
xgrid(1);
xtitle("Lugar das Raízes - Planta Reduzida Compensada", "Eixo Real", "Eixo Imaginário");

// Item e) - Funções de transferência de malha fechada na PLANTA COMPLETA:
T_diof    = (C_diof * G_full) /. 1;
T_lr_full = (C_lr_full * G_full) /. 1;
T_lr_red  = (C_lr_red * G_full) /. 1;

t_sim = 0:0.01:6;
y_diof    = csim('step', t_sim, T_diof);
y_lr_full = csim('step', t_sim, T_lr_full);
y_lr_red  = csim('step', t_sim, T_lr_red);

// Imagem 3: Comparação de TODAS as Respostas ao Degrau - Planta Completa
scf(3); clf;
plot(t_sim, y_diof,    'b-',  'LineWidth', 2);
plot(t_sim, y_lr_full, 'r--', 'LineWidth', 2);
plot(t_sim, y_lr_red,  'g-.', 'LineWidth', 2);
plot(t_sim, ones(t_sim),'k:',  'LineWidth', 1);
xgrid(1);
xtitle("Comparação das Respostas ao Degrau (Planta Completa)", "Tempo (s)", "Amplitude y(t)");
legend(["Compensador Diofantino (Item a)"; ...
        "Compensador LR Planta Completa (Item b)"; ...
        "Compensador LR Planta Reduzida (Item d)"; ...
        "Referência degrau unitário"]);

printf("\n--- DESEMPENHO NO MODELO COMPLETO ---\n");
printf("Diofantino:  y(inf) = %.4f | Max = %.4f\n", y_diof($), max(y_diof));
printf("LR Completo: y(inf) = %.4f | Max = %.4f\n", y_lr_full($), max(y_lr_full));
printf("LR Reduzido: y(inf) = %.4f | Max = %.4f\n", y_lr_red($), max(y_lr_red));
