// Exercicio 2 - g(s) = 1/(s(s+1)(s+2)), c(s) = 6
clear; s = poly(0,'s');
g = syslin('c', 1/(s*(s+1)*(s+2)));
c = 6; L = c*g;

// a)
mprintf("\n--- a) ---\n");
wc = sqrt(2);
mprintf("L(j*sqrt(2)) = %s  (passa por -1 => marginalmente estavel)\n", string(horner(L.num,%i*wc)/horner(L.den,%i*wc)));
mprintf("Polos de malha fechada:\n"); disp(roots(L.den + L.num));
f = scf(); nyquist(L, 0.05, 2);
xs2png(f, "ex2_a-diagrama_de_nyquist.png");

// b)
mprintf("\n--- b) ---\n");
[gm, fr] = g_margin(L); [pm, fp] = p_margin(L);
mprintf("Margem de ganho = %.4f dB (w = %.4f rad/s)\n", gm, fr*2*%pi);
mprintf("Margem de fase  = %.4f graus\n", pm);
f = scf(); black(L, 0.05, 2);
xs2png(f, "ex2_b-diagrama_de_black.png");

// c)
mprintf("\n--- c) ---\n");
T = syslin('c', L.num, L.den + L.num);
dt = 0.01;  // fs = 100 Hz >> 2*0.225 Hz (teorema da amostragem respeitado)
mprintf("Freq. entrada = %.4f Hz, freq. amostragem = %g Hz\n", sqrt(2)/(2*%pi), 1/dt);
mprintf("Polos de MF em +-j*sqrt(2): entrada na ressonancia => saida cresce linearmente\n");
t = 0:dt:60;
deff('y=u(t)', 'y=sin(sqrt(2)*t)');
y = csim(u, t, T);
f = scf(); plot(t, u(t), 'b', t, y, 'r'); legend("u","y");
xs2png(f, "ex2_c-simulacao.png");
