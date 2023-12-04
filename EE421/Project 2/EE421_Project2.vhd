library ieee;
library work;
use work.fsm_types.all;
use ieee.std_logic_1164.all;

entity EE421_Project2 is
    port( clock, resetn, w, en: in std_logic;
			            d0,d1, d2: out std_logic_vector(6 downto 0);
			                    z: out std_logic);
end EE421_Project2;

architecture Behavior of EE421_Project2 is	
	component Decod7segInput
		port( w: in std_logic;
				d0: out std_logic_vector(6 downto 0));
	end component;
	
	component Decod7segState
		port( state: in state_type;
				d1: out std_logic_vector(6 downto 0));
	end component;

	signal y_present, y_next: state_type;
	
	begin
	
	state_register: process(en, resetn)
	begin
		if resetn='0' then
			y_present <= Reset;
		elsif(en'event and en='1') then
			y_present <= y_next;
		end if;	
	end process state_register;
		
	
	next_state_logic: process(w)
	begin	
		case y_present is
			when Reset =>
				if w='0' then
					y_next <= H;
				else 
					y_next <= A;
				end if;
			when A =>
				if w='0' then
					y_next <= B;
				else 
					y_next <= E;
				end if;
			when  B =>
				if w='0' then
					y_next <= C;
				else 
					y_next <= A;
				end if;
			when  C =>
				if w='0' then
					y_next <= I;
				else 
					y_next <= D;
				end if;
			when D =>
				if w='0' then
					y_next <= B;
				else 
					y_next <= K;
				end if;
			when E =>
				if w='0' then
					y_next <= B;
				else 
					y_next <= F;
				end if;
			when F =>
				if w='0' then
					y_next <= B;
				else 
					y_next <= G;
				end if;
			when G =>
				if w='0' then
					y_next <= B;
				else 
					y_next <= G;
				end if;
			when H =>
				if w='0' then
					y_next <= I;
				else 
					y_next <= A;
				end if;
			when I =>
				if w='0' then
					y_next <= I;
				else 
					y_next <= J;
				end if;
			when J =>
				if w='0' then
					y_next <= B;
				else 
					y_next <= K;
				end if;
			when K =>
				if w='0' then
					y_next <= B;
				else 
					y_next <= F;
				end if;
			when others =>
				y_next <= Reset;
		end case;
	end process next_state_logic;
	
	output_logic: process(y_present)
	begin
		case y_present is
			when D =>
                z <= '1';
			when K =>
                z <= '1';
		   when G =>
                z <= '1';
			when others =>
				 z <= '0';
        end case;
   end process output_logic;
		
	DecodeLED: Decod7segInput port map(w, d0);
	DecodeState: Decod7segState port map(y_present, d1);
	DecodeNextState: Decod7segState port map(y_next, d2);
	 
end Behavior;

-- Decode7SegState Code
library ieee;
library work;
use work.fsm_types.all;
use ieee.std_logic_1164.all;

entity Decod7segState is
    port( state : in state_type;
          d1 : out std_logic_vector(6 downto 0));
end Decod7segState;

architecture structure of Decod7segState is
begin
    d1 <= "0001000" when state=A else
			 "0000000" when state=B else
			 "1000110" when state=C else
			 "1100000" when state=D else
			 "0000110" when state=E else
			 "0001110" when state=F else
			 "1000010" when state=G else
			 "0001001" when state=H else
			 "1001111" when state=I else
			 "1110001" when state=J else
			 "0001010" when state=K else
			 "0000100" when state=Reset else
			 "1111111";
end structure;			

-- Decode7Seg Code
library IEEE;
use IEEE.Std_logic_1164.all;

entity Decod7segInput is
    port( w : in std_logic;
          d0 : out std_logic_vector(6 downto 0));
end Decod7segInput;

architecture structure of Decod7segInput is
begin
    d0 <= "1111001" when w='1' else "1000000";
end structure;
					
				
		