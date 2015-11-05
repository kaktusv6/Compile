// Распознавание программы на простом языке. Распознаватель лексем (лексер)
// { 
//   Лексемы:
//   ;  :=  +=  -=  *=  id  num  begin  end  cycle
 
//   Ключевые слова:
//   begin  end  cycle
// }
unit SimpleLangLexer;
 
interface
 
// TLex - перечислимый тип - все лексемы грамматики
// lexEot - конец текста программы
type 
  Tok = (EOF, ID, INUM, COLON, SEMICOLON, ASSIGN, &BEGIN, &END, CYCLE);
 
var 
  fname: string;           // Имя файла программы
  LexRow,LexCol: integer;  // Строка-столбец начала лексемы. Конец лексемы = LexCol+Length(LexText)
  LexKind: Tok;            // Тип лексемы   
  LexText: string;         // Текст лексемы
  LexValue: integer;       // Целое значение, связанное с лексемой lexNum
 
procedure NextLexem;
procedure Init(fn: string);
procedure Done;
function TokToString(t: Tok): string;
 
implementation
 
var 
  ch: Char;         // Текущий символ
  f: text;          // Текущий файл
  row,col: integer; // Текущие строка и столбец в файле
  KeywordsMap := new Dictionary<string,Tok>; // Словарь, сопоставляющий ключевым словам константы типа TLex. Инициализируется процедурой InitKeywords
 
 
procedure LexError(message: string); // ошибка лексического анализатора
begin
  var ss := System.IO.File.ReadLines(fname).Skip(row-1).First(); // Строка row файла
  writeln('Лексическая ошибка в строке ',row,':');
  writeln(ss);
  writeln('^':col-1);
  if message<>'' then 
    writeln(message);
  Done;
  halt;
end;
 
procedure NextCh;
begin
  // В LexText накапливается предыдущий символ и считывается следующий символ
  LexText += ch;
  if not f.Eof then
  begin
    read(f,ch);
    if ch<>#10 then
      col += 1
    else
    begin
      row += 1;
      col := 1;
    end;
  end
  else 
  begin
    ch := #0; // если достигнут конец файла, то возвращается #0
    Done;
  end;
end; 
 
procedure PassSpaces;
begin
  while char.IsWhiteSpace(ch) do
    NextCh;
end;
 
procedure NextLexem;
begin
  PassSpaces;
  // R К этому моменту первый символ лексемы считан в ch
  LexText := '';
  LexRow := Row;
  LexCol := Col;
// Тип лексемы определяется по ее первому символу
// Для каждой лексемы строится синтаксическая диаграмма
  case ch of
  ';': begin
         NextCh;
         LexKind := Tok.SEMICOLON;
       end;  
  ':': begin
         NextCh;
         if ch<>'=' then 
           lexerror('= ожидалось');
         NextCh;
         LexKind := Tok.ASSIGN;
       end;
  'a'..'z': begin
         while ch in ['a'..'z','0'..'9'] do
           NextCh;
         if KeywordsMap.ContainsKey(LexText) then
           LexKind := KeywordsMap[LexText]
         else LexKind := Tok.ID;
       end;
  '0'..'9': begin
         while char.IsDigit(ch) do
           NextCh;
         LexValue := integer.Parse(LexText);
         LexKind := Tok.INUM;
       end;
    #0: LexKind := Tok.EOF;   
    else lexerror('Неверный символ '+ch);
  end;  
end;
 
procedure InitKeywords;
begin
  KeywordsMap['begin'] := Tok.&BEGIN;
  KeywordsMap['end'] := Tok.&END;
  KeywordsMap['cycle'] := Tok.CYCLE;
end;
 
procedure Init(fn: string);
begin
  InitKeywords;
  fname := fn;
  AssignFile(f,fname);
  reset(f);
  row := 1; col := 1;
  NextCh;    // Считать первый символ в ch
  NextLexem; // Считать первую лексему, заполнив LexText, LexKind и, возможно, LexValue
end;
 
procedure Done;
begin
  close(f);
end;
 
function TokToString(t: Tok): string;
begin
  Result := t.ToString;
  case t of
Tok.ID:   Result += ' ' + LexText;
Tok.INUM: Result += ' ' + LexValue; 
  end;
end;
 
end.