function quest(B1, B2, R1, R2, w1, w2)

% Unit vector
b1 = B1 / sqrt(B1(1) * B1(1) + B1(2) * B1(2) + B1(3) * B1(3));
b2 = B2 / sqrt(B2(1) * B2(1) + B2(2) * B2(2) + B2(3) * B2(3));

r1 = R1 / sqrt((R1(1) * R1(1) + R1(2) * R1(2) + R1(3) * R1(3)));
r2 = R2 / sqrt((R2(1) * R2(1) + R2(2) * R2(2) + R2(3) * R2(3)));

% Attitude Profile Matrix
B = w1 * transpose(b1) * r1 + w2 * (transpose(b2)) * r2;

% Different elements
t = [(B(2,3) - B(3,2)) (B(3,1) - B(1,3)) (B(1,2) - B(2,1))];
t_trans = transpose(t);
S = B + transpose(B);
sigma = trace(B);
a = sigma * sigma - trace(adjoint(S));
b = sigma * sigma + t * t_trans;
c = det(S) + t * S * t_trans;
d = t * S * S * t_trans;

% Newton-Raphson Method for lambda
Lam0 = w1 + w2;
lamn = 0;
lama = Lam0;
while abs(lama - lamn) > 0.000001
    lamn = lama;
    lama = lama - (lama * lama * lama * lama - (a + b) * lama * lama - c * lama + (a * b + c * sigma - d)) / (4 * lama * lama * lama - 2 * (a + b) * lama - c);
end

% Equations for Qopt
alpha = lama * lama - sigma * sigma + trace(adjoint(S));
beta = lama - sigma;
Y = (lama + sigma) * alpha - det(S);
X = (alpha * eye(3) + beta * S + S * S) * t_trans;
g = X(1) * X(1) + X(2) * X(2) + X(3) * X(3);
y = Y * Y;
e = sqrt(y + g);
E = 1 / e;
x = transpose(X);
x = [x Y];
u = transpose(x);

% Optimal Quaternion (x, y, z, w)
P = E * u;
fprintf('x : %f, y : %f, z : %f, w : %f\n', P(1), P(2), P(3), P(4));

% DCM
R11 = 1 - 2 * (P(2) * P(2) + P(3) * P(3));
R21 = 2 * P(1) * P(2) + P(4) * P(3);
R32 = 2 * P(2) * P(3) + P(4) * P(1);
R33 = 1 - 2 * (P(1) * P(1) + P(2) * P(2));
R13 = 2 * P(1) * P(3) - P(4) * P(2);

% Euler Angles
phi = atand(R32 / R33);
theta = atand(-R13);
psi = atand(R21 / R11);
fprintf('phi : %f\n',phi);
fprintf('theta : %f\n',theta);
fprintf('psi : %f\n',psi);

end