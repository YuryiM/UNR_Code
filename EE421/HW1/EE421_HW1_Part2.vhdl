library ieee;
use ieee.std_logic_1164.all;

entity EE421_VHDL_HW1 is port(
    v3,v2,v1,v0 in std_logic;
    d0,d1 out std_logic_vector(6 downto 0));
end EE421_VHDL_HW1;

architecture structure of EE421_VHDL_HW1 is
    component comparator is port(
        v3,v2,v1,v0 in std_logic;
        zout std_logic);
    end component;

    component circuitA is port(
        v2,v1,v0 in std_logic;
        m2,m1,m0 out std_logic);
    end component;

    component multi2to1 is port(
        x0,x1,s in std_logic;
        m out std_logic);
    end component;

    component circuitB is port(
        zin std_logic;
        d1 out std_logic_vector(6 downto 0));
    end component;

    component Decod7seg is port(
        a in std_logic_vector(3 downto 0);
        f out std_logic_vector(6 downto 0));
    end component;

    signal z, m0, m1, m2, m3, a2,a1,a0 std_logic;
    signal temp0 std_logic_vector(3 downto 0);

begin
    temp0 = m3 & m2 & m1 & m0;

    L0 comparator port map (v3,v2,v1,v0,z);
    L1 circuitA port map (v2,v1,v0,a2,a1,a0);
    L2 multi2to1 port map(v3,'0',z,m3);
    L3 multi2to1 port map(v2,a2,z,m2);
    L4 multi2to1 port map(v1,a1,z,m1);
    L5 multi2to1 port map(v0,a0,z,m0);
    L6 circuitB port map(z,d1);
    L7 Decod7seg port map(temp0,d0);
end structure;


-- Comparator Code
library ieee;
use ieee.std_logic_1164.all;

entity comparator is port(
    v3, v2, v1, v0 in std_logic;
    z out std_logic);
end comparator;

architecture logic of comparator is
begin
    z = (v3 and v1) or (v3 and v2);
end logic;



-- Circuit A Code
library ieee;
use ieee.std_logic_1164.all;

entity circuitA is port(
    v2, v1, v0 in std_logic;
    m2, m1, m0 out std_logic);
end circuitA;

architecture structure of circuitA is
begin
    m2 = v2 and v1;
    m1 = not v1;
    m0 = v0;
end structure;



-- Multi2To1 Code
library ieee;
use ieee.std_logic_1164.all;

entity multi2to1 is port(
    x0, x1, s in std_logic;
    m out std_logic);
end multi2to1;

architecture logic of multi2to1 is
begin
    m = x1 when (s = '1') else x0;
end logic;



-- CircuitB Code
library ieee;
use ieee.std_logic_1164.all;

entity circuitB is port(
    z in std_logic;
    d1 out std_logic_vector(6 downto 0));
end circuitB;

architecture logic of circuitB is
begin
    d1 = 1111001 when (z = '1') else 1000000;
end logic;



-- Decode7Seg Code
library IEEE;
use IEEE.Std_logic_1164.all;

entity Decod7seg is
    port( a  in std_logic_vector(3 downto 0);
          f  out std_logic_vector(6 downto 0));
end Decod7seg;

architecture structure of Decod7seg is
begin
    f = 0000001 when a = 0000 else -- 0
         1001111 when a = 0001 else -- 1
         0010010 when a = 0010 else -- 2
         0000110 when a = 0011 else -- 3
         1001100 when a = 0100 else -- 4
         0100100 when a = 0101 else -- 5
         0100000 when a = 0110 else -- 6
         0001111 when a = 0111 else -- 7
         0000000 when a = 1000 else -- 8
         0001100 when a = 1001 else -- 9
         0000001 when a = 1010 else -- 10
         1001111 when a = 1011 else -- 11
         0010010 when a = 1100 else -- 12
         0000110 when a = 1101 else -- 13
         1001100 when a = 1110 else -- 14
         0100100 when a = 1111 else -- 15
         1111111;
end structure;