-- Project 1
library ieee;
use ieee.std_logic_1164.all;

entity Project1_Binary is port(
	sel: in std_logic_vector(1 downto 0);
	Cin: in std_logic;
	A, B: in std_logic_vector(3 downto 0);
	AL, BL: out std_logic_vector(3 downto 0);
	CinL: out std_logic;
	selLED: out std_logic_vector(1 downto 0);
	d0, d1, d2, d3, d4: out std_logic_vector(6 downto 0));
end Project1_Binary;

architecture logic of Project1_Binary is
	component multi3to1
		port(x: in std_logic_vector(3 downto 0);
			  s: in std_logic_vector(1 downto 0);
			  m: out std_logic_vector(3 downto 0));
	end component;
	
	component multi2to1fourbit 
		port(x0, x1: in std_logic_vector(3 downto 0);
			  s: in std_logic;
			  m: out std_logic_vector(3 downto 0));
	end component;
	
	component Full_Adder
        port( A, B, Cin : in STD_LOGIC;
              S, Cout : out STD_LOGIC);
    end component;
	 
	 component Decod7seg
			port( A : in std_logic_vector(3 downto 0);
					Cout: in std_logic;
          f0,f1,f2,f3,f4 : out std_logic_vector(6 downto 0));
	 end component;
	 signal D, C, B0, S, cXOR: std_logic_vector(3 downto 0);
	 signal c0,c1, c2, c3, Cin0, Cout, sel3: std_logic;
begin
	CinL <= Cin;
	Cin0 <= not Cin;
	selLED <= sel;
	AL <= A;
	BL <= B;
	sel3 <= sel(0) AND sel(1);
	cXOR <= A XOR B;
--	CoutLED <= not Cout;
	
	Multi3: multi3to1 port map(B, sel, B0);
	
	FA1: Full_Adder port map( A(0), B0(0), Cin0, S(0), c1);
	FA2: Full_Adder port map( A(1), B0(1), c1, S(1), c2);
	FA3: Full_Adder port map( A(2), B0(2), c2, S(2), c3);
	FA4: Full_Adder port map( A(3), B0(3), c3, S(3), Cout);
	
	Multi2: multi2to1fourbit port map(cXOR, S, sel3, D); 
	
	Decode: Decod7seg port map(D, Cout, d0, d1, d2, d3, d4);
end logic; 


-- Multi2To1 4 bit Code
library ieee;
use ieee.std_logic_1164.all;

entity multi2to1fourbit is port(
    x0, x1: in std_logic_vector(3 downto 0);
	 s: in std_logic;
    m: out std_logic_vector(3 downto 0));
end multi2to1fourbit;

architecture logic of multi2to1fourbit is
begin
    m <= x0 when (s = '1') else x1;
end logic;


-- Multiplexer 3 to 1 
library ieee;
use ieee.std_logic_1164.all;

entity multi3to1 is port(
    x: in std_logic_vector(3 downto 0);
	 s: in std_logic_vector(1 downto 0);
    m: out std_logic_vector(3 downto 0));
end multi3to1;

architecture logic of multi3to1 is
begin
with s select
    m <= x when "01",
			not x when "10",
			"0000" when "00",
			"XXXX" when others;
end logic;

-- Full Adder

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

-- Multi2To1 Code
library ieee;
use ieee.std_logic_1164.all;

entity multi2to1 is port(
    x0, x1, s: in std_logic;
    m: out std_logic);
end multi2to1;

architecture structure of multi2to1 is
begin
    m <= x1 when (s = '1') else x0;
end structure;

-- Decode7Seg Code
library IEEE;
use IEEE.Std_logic_1164.all;

entity Decod7seg is
    port( A : in std_logic_vector(3 downto 0);
			 Cout: in std_logic;
          f0,f1,f2,f3,f4 : out std_logic_vector(6 downto 0));
end Decod7seg;

architecture structure of Decod7seg is
begin
    -- For A(0)
    f0 <= "1111001" when A(0)='1' else "1000000";

    -- For A(1)
    f1 <= "1111001" when A(1)='1' else "1000000";

    -- For A(2)
    f2 <= "1111001" when A(2)='1' else "1000000";

    -- For A(3)
    f3 <= "1111001" when A(3)='1' else "1000000";
	 
	 f4 <= "1111001" when Cout='1' else "1000000";
	 
end structure;