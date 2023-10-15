-- Part 3
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity EE421_VHDL_HW1 is
    port( A, B : in STD_LOGIC_VECTOR (3 downto 0);
          Cin : in STD_LOGIC;
          Cout : out STD_LOGIC;
			 AL, BL : out STD_LOGIC_VECTOR(3 downto 0);
			 CinL : out STD_LOGIC;
			 d0, d1: out std_logic_vector(6 downto 0));
end EE421_VHDL_HW1;

architecture Behavioral of EE421_VHDL_HW1 is
    component Full_Adder
        port( A, B, Cin : in STD_LOGIC;
              S, Cout : out STD_LOGIC);
    end component;
	 
	 component converter
			port( v3,v2,v1,v0: in std_logic;
					d0,d1: out std_logic_vector(6 downto 0));
	 end component;
	 
    signal c1, c2, c3: STD_LOGIC;
	 signal S: std_logic_vector(3 downto 0); 
begin
	 
    FA1: Full_Adder port map( A(0), B(0), Cin, S(0), c1);
    FA2: Full_Adder port map( A(1), B(1), c1, S(1), c2);
    FA3: Full_Adder port map( A(2), B(2), c2, S(2), c3);
    FA4: Full_Adder port map( A(3), B(3), c3, S(3), Cout);
	 AL <= A;
	 BL <= B;
	 CinL <= Cin;
	 Convert1: converter port map (S(3), S(2), S(1), S(0), d0, d1);
	 
end Behavioral;

library ieee;
use ieee.std_logic_1164.all;

entity Full_Adder is
    port( A, B, Cin : in std_logic;
          S, Cout : out std_logic);
end Full_Adder;

architecture structural of Full_Adder is
    signal a1, a2, a3: std_logic;

begin
    a1 <= A xor B;
    a2 <= A and B;
    a3 <= a1 and Cin;
    S <= a1 xor Cin;
    Cout <= a2 or a3;
end structural;




-- Part 2
library ieee;
use ieee.std_logic_1164.all;

entity converter is port(
    v3,v2,v1,v0: in std_logic;
    d0,d1: out std_logic_vector(6 downto 0));
end converter;

architecture structure of converter is
    component comparator is port(
        v3,v2,v1,v0: in std_logic;
        z:out std_logic);
    end component;

    component circuitA is port(
        v2,v1,v0: in std_logic;
        m2,m1,m0: out std_logic);
    end component;

    component multi2to1 is port(
        x0,x1,s: in std_logic;
        m: out std_logic);
    end component;

    component circuitB is port(
        z:in std_logic;
        d1: out std_logic_vector(6 downto 0));
    end component;

    component Decod7seg is port(
        a: in std_logic_vector(3 downto 0);
        f: out std_logic_vector(6 downto 0));
    end component;

    signal z, m0, m1, m2, m3, a2,a1,a0: std_logic;
    signal temp0: std_logic_vector(3 downto 0);

begin
    temp0 <= m3 & m2 & m1 & m0;

    L0: comparator port map (v3,v2,v1,v0,z);
    L1: circuitA port map (v2,v1,v0,a2,a1,a0);
    L2: multi2to1 port map(v3,'0',z,m3);
    L3: multi2to1 port map(v2,a2,z,m2);
    L4: multi2to1 port map(v1,a1,z,m1);
    L5: multi2to1 port map(v0,a0,z,m0);
    L6: circuitB port map(z,d1);
    L7: Decod7seg port map(temp0,d0);
end structure;


-- Comparator Code
library ieee;
use ieee.std_logic_1164.all;

entity comparator is port(
    v3, v2, v1, v0: in std_logic;
    z: out std_logic);
end comparator;

architecture logic of comparator is
begin
    z <= (v3 and v1) or (v3 and v2);
end logic;



-- Circuit A Code
library ieee;
use ieee.std_logic_1164.all;

entity circuitA is port(
    v2, v1, v0: in std_logic;
    m2, m1, m0: out std_logic);
end circuitA;

architecture structure of circuitA is
begin
    m2 <= v2 and v1;
    m1 <= not v1;
    m0 <= v0;
end structure;



-- Multi2To1 Code
library ieee;
use ieee.std_logic_1164.all;

entity multi2to1 is port(
    x0, x1, s: in std_logic;
    m: out std_logic);
end multi2to1;

architecture logic of multi2to1 is
begin
    m <= x1 when (s = '1') else x0;
end logic;



-- CircuitB Code
library ieee;
use ieee.std_logic_1164.all;

entity circuitB is port(
    z: in std_logic;
    d1: out std_logic_vector(6 downto 0));
end circuitB;

architecture logic of circuitB is
begin
    d1 <= "1111001" when (z = '1') else "1000000";
end logic;



-- Decode7Seg Code
library IEEE;
use IEEE.Std_logic_1164.all;

entity Decod7seg is
    port( a : in std_logic_vector(3 downto 0);
          f : out std_logic_vector(6 downto 0));
end Decod7seg;

architecture structure of Decod7seg is
begin
    f <= "0000001" when a = "0000" else -- 0
         "1001111" when a = "0001" else -- 1
         "0010010" when a = "0010" else -- 2
         "0000110" when a = "0011" else -- 3
         "1001100" when a = "0100" else -- 4
         "0100100" when a = "0101" else -- 5
         "0100000" when a = "0110" else -- 6
         "0001111" when a = "0111" else -- 7
         "0000000" when a = "1000" else -- 8
         "0001100" when a = "1001" else -- 9
         "0000001" when a = "1010" else -- 10
         "1001111" when a = "1011" else -- 11
         "0010010" when a = "1100" else -- 12
         "0000110" when a = "1101" else -- 13
         "1001100" when a = "1110" else -- 14
         "0100100" when a = "1111" else -- 15
         "1111111";
end structure;