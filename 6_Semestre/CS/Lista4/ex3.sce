// Exercicio 3 - Tanques: x = [h1; h2], u = q, y = h2
clear;
C1 = 1.5; C2 = 0.8; R1 = 2; R2 = 3;
A = [-1/(R1*C1), 1/(R1*C1); 1/(R1*C2), -(1/R1+1/R2)/C2];
B = [1/C1; 0];
C = [0 1]; D = 0;

// a)
mprintf("\n--- a) ---\n");
Co = cont_mat(A,B); Ob = obsv_mat(A,C);
disp("A =", A, "B =", B, "Controlabilidade =", Co, "Observabilidade =", Ob);
mprintf("rank(Co) = %d, rank(Ob) = %d (n = 2)\n", rank(Co), rank(Ob));

// b)  OS<15% -> zeta>0.517 ; ts5% = 3/(zeta*wn) < 10 -> zeta*wn > 0.3
mprintf("\n--- b) ---\n");
zeta = 0.7; sig = 0.6; wn = sig/zeta;
p = [-sig+%i*wn*sqrt(1-zeta^2), -sig-%i*wn*sqrt(1-zeta^2)];
K = ppol(A,B,p);
N = -1/(C*inv(A-B*K)*B);
mprintf("zeta = %.2f, wn = %.4f, OS = %.2f%%, ts = %.2f s\n", zeta, wn, 100*exp(-zeta*%pi/sqrt(1-zeta^2)), 3/sig);
disp("Polos desejados =", p, "K =", K, "N =", N);

// c)
mprintf("\n--- c) ---\n");
Lo = ppol(A',C',2*p)';
disp("Polos observador =", 2*p, "L =", Lo);
// estado aumentado [x; xh]
Aa = [A, -B*K; Lo*C, A-B*K-Lo*C];
Ba = [B*N; B*N];
Ca = [C, zeros(1,2)];
disp("Autovalores MF (c) =", spec(Aa));

// d)
mprintf("\n--- d) ---\n");
t = 0:0.05:20;
sb = syslin('c', A-B*K, B*N, C, D);
sc = syslin('c', Aa, Ba, Ca, 0);
yb = csim('step', t, sb); yc = csim('step', t, sc);
mprintf("y(final) b = %.4f, c = %.4f\n", yb($), yc($));
f = scf(); plot(t, yb, 'b', t, yc, 'r--');
legend("Realim. estado","Realim. dinamica saida"); xgrid();
xs2png(f, "ex3_d-simulacao.png");

// e)  A'P + P A = -I
mprintf("\n--- e) ---\n");
Pb = lyap(A-B*K, -eye(2,2), 'c');
Pc = lyap(Aa, -eye(4,4), 'c');
mprintf("V(x) = x'' P x ; P > 0 se todos autovalores > 0\n");
mprintf("(b) estado x = [h1; h2]\n"); disp(Pb); mprintf("autovalores:\n"); disp(spec(Pb));
mprintf("(c) estado [x; xh] = [h1; h2; h1h; h2h]\n"); disp(Pc); mprintf("autovalores:\n"); disp(spec(Pc));
