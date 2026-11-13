// Exercicio 1 - Suspensao: G(s) = (b s + k)/(m s^2 + b s + k)
clear; s = poly(0,'s');
m = 400; b = 200;

// a)
mprintf("\n--- a) ---\n");
mprintf("0.4<zeta<0.8  =>  %.2f < k < %.2f  (k = b^2/(4 m zeta^2))\n", b^2/(4*m*0.8^2), b^2/(4*m*0.4^2));
k = 70;
wn = sqrt(k/m); zeta = b/(2*sqrt(k*m));
mprintf("k = %g N/m, wn = %.4f rad/s, zeta = %.4f\n", k, wn, zeta);
G = syslin('c', (b*s+k)/(m*s^2+b*s+k));
disp(G);

// b)
mprintf("\n--- b) ---\n");
A = 0.05;
for w = [10 20]
    g = abs(horner(G.num,%i*w)/horner(G.den,%i*w));
    mprintf("w = %d rad/s: |G| = %.5f, amplitude saida = %.5f m\n", w, g, A*g);
end

// c)
f = scf(); bode(G, 0.01/(2*%pi), 100/(2*%pi));
xs2png(f, "ex1_c-diagrama_de_bode.png");

// d)
t = 0:0.005:10;
f = scf();
i = 1;
for w = [10 20]
    deff('y=u(t)', 'y=' + string(A) + '*sin(' + string(w) + '*t)');
    y = csim(u, t, G);
    subplot(2,1,i); plot(t, u(t), 'b', t, y, 'r');
    legend("u (solo)","y (massa)"); title("w = " + string(w) + " rad/s");
    i = i + 1;
end
xs2png(f, "ex1_d-simulacao.png");
