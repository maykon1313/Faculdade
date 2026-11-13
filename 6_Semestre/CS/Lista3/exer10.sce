// Limpa console e figuras anteriores
clc;
clf();

// 1. Matrizes da planta (extraídas do Exercício 10)
A = [1,  2, -3; 
     2, -3,  0; 
     1,  0, -1];
B = [1; 1; 0];
C = [1, -0.5, 0];
D = 0;

// 2. Matrizes de ponderação do critério de custo J
Q = diag([3, 0, 0]);
R = 1.2;

// 3. Resolução da Equação Algébrica de Riccati e cálculo do ganho ótimo K
P = riccati(A, B * inv(R) * B', Q, 'c');
K = inv(R) * B' * P;

disp("Matriz P (Riccati):");
disp(P);
disp("Ganho ótimo K:");
disp(K);

// 4. Dinâmica em Malha Fechada: x_dot = (A - B*K)x
A_mf = A - B * K;

// 5. Simulação da resposta no tempo a partir de uma condição inicial
// Para o sistema com a saída escalar y(t):
sys_cl = syslin('c', A_mf, B, C, D);

t = 0:0.01:10;       // Intervalo de tempo: 0 a 10 s
x0 = [1; 1; 1];      // Condição inicial arbitrária não-nula

// Resposta da saída y(t)
y = csim('initial', t, sys_cl, x0);

// Para observar todos os estados x(t), usamos C = eye(3,3) e D = zeros(3,1)
sys_estados = syslin('c', A_mf, B, eye(3, 3), zeros(3, 1));
x = csim('initial', t, sys_estados, x0);

// 6. Visualização Gráfica
subplot(2, 1, 1);
plot(t, y, 'r-', 'LineWidth', 2);
xgrid();
title("Saída y(t) do Sistema em Malha Fechada (LQR)");
xlabel("Tempo (s)");
ylabel("y(t)");

subplot(2, 1, 2);
plot(t, x(1, :), 'b-', 'LineWidth', 1.5);
plot(t, x(2, :), 'g--', 'LineWidth', 1.5);
plot(t, x(3, :), 'm-.', 'LineWidth', 1.5);
xgrid();
title("Evolução dos Estados x(t)");
xlabel("Tempo (s)");
ylabel("Estados");
legend(["x1", "x2", "x3"]);
