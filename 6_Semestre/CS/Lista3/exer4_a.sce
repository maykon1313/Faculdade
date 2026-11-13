clear; clc; clf;

w    = [0.01, 0.05, 0.1, 0.5, 1, 5, 10, 100, 1000];
amp  = [0.166, 0.166, 0.166, 0.158, 0.141, 0.03, 0.01, 1e-4, 1e-6];
fase = [0.5, -2.4, -4.8, -23.8, -45, -127.2, -152, -176, -179];

mag_dB = 20 * log10(amp);

// ---------- Gráfico de Magnitude ----------
subplot(2,1,1);
plot2d(w, mag_dB, style=2,  logflag="ln");   // retas entre os pontos
plot2d(w, mag_dB, style=-9, logflag="ln");   // marcadores (círculos) nos pontos

a = gca();
a.log_flags     = "lnn";                     // x logarítmico, y linear
a.data_bounds   = [0.01, -140; 1000, 0];     // limites exatos do papel
a.tight_limits  = "on";
a.y_ticks       = tlist(["ticks","locations","labels"], -140:20:0, string(-140:20:0));
a.sub_ticks     = [8, 1];                    // 8 subdivisões em cada década (2..9)
xgrid(color("gray"));

// valor exato de cada ponto
for i = 1:length(w)
    xstring(w(i), mag_dB(i), msprintf(" (%g; %.1f)", w(i), mag_dB(i)));
    gce().font_size = 1;
end

ylabel("Magnitude (dB)");
title("Diagrama de Bode da Planta");

// ---------- Gráfico de Fase ----------
subplot(2,1,2);
plot2d(w, fase, style=2,  logflag="ln");
plot2d(w, fase, style=-9, logflag="ln");

a = gca();
a.log_flags     = "lnn";
a.data_bounds   = [0.01, -180; 1000, 30];
a.tight_limits  = "on";
a.y_ticks       = tlist(["ticks","locations","labels"], -180:30:30, string(-180:30:30));
a.sub_ticks     = [8, 1];
xgrid(color("gray"));

for i = 1:length(w)
    xstring(w(i), fase(i), msprintf(" (%g; %.1f)", w(i), fase(i)));
    gce().font_size = 1;
end

xlabel("Frequência (rad/s)");
ylabel("Fase (graus)");

// ---------- Tabela dos pontos no console ----------
mprintf("\n  w (rad/s)   |amp|     Mag (dB)   Fase (graus)\n");
for i = 1:length(w)
    mprintf("  %-10g  %-8.2e  %-9.2f  %-8.1f\n", w(i), amp(i), mag_dB(i), fase(i));
end
