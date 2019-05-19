; ModuleID = 'bubble_sort'
source_filename = "bubble_sort"

@format = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@format.1 = private unnamed_addr constant [3 x i8] c"%d\00"

declare i32 @printf(i8*, ...)

define internal void @echo(i32) {
entry:
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format, i32 0, i32 0), i32 %0)
  ret void
}

declare i32 @scanf(i8*, ...)

define internal i32 @read() {
entry:
  %toScan = alloca i32
  %0 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.1, i32 0, i32 0), i32* %toScan)
  %1 = load i32, i32* %toScan
  ret i32 %1
}

declare i32 @rand()

; Function Attrs: nounwind
define dso_local i32 @main() #0 !dbg !4 {
entry:
  %iterations = alloca i32, !dbg !8
  store i32 1024, i32* %iterations, !dbg !8
  %n = alloca i32, !dbg !9
  store i32 512, i32* %n, !dbg !9
  %numbers = alloca [512 x i32], !dbg !10
  %seed = alloca i32, !dbg !11
  store i32 1, i32* %seed, !dbg !11
  %i = alloca i32, !dbg !12
  %j = alloca i32, !dbg !13
  %a = alloca i32, !dbg !14
  %b = alloca i32, !dbg !15
  %switches = alloca i32, !dbg !16
  %rand = alloca i32, !dbg !17
  br label %for.init, !dbg !18

for.init:                                         ; preds = %entry
  store i32 0, i32* %i, !dbg !19
  br label %for.cond, !dbg !19

for.cond:                                         ; preds = %for.inc, %for.init
  %0 = load i32, i32* %i, !dbg !20
  %1 = load i32, i32* %iterations, !dbg !21
  %2 = icmp slt i32 %0, %1, !dbg !20
  br i1 %2, label %for.body, label %for.end, !dbg !20

for.body:                                         ; preds = %for.cond
  br label %for.init1, !dbg !22

for.inc:                                          ; preds = %while.end
  %3 = load i32, i32* %i, !dbg !23
  %4 = add i32 %3, 1, !dbg !23
  store i32 %4, i32* %i, !dbg !24
  br label %for.cond, !dbg !24

for.end:                                          ; preds = %for.cond
  %sorted = alloca i32, !dbg !25
  store i32 1, i32* %sorted, !dbg !25
  br label %for.init11, !dbg !26

for.init1:                                        ; preds = %for.body
  store i32 0, i32* %j, !dbg !27
  br label %for.cond2, !dbg !27

for.cond2:                                        ; preds = %for.inc4, %for.init1
  %5 = load i32, i32* %j, !dbg !28
  %6 = load i32, i32* %n, !dbg !29
  %7 = icmp slt i32 %5, %6, !dbg !28
  br i1 %7, label %for.body3, label %for.end5, !dbg !28

for.body3:                                        ; preds = %for.cond2
  %8 = load i32, i32* %seed, !dbg !30
  %9 = mul i32 %8, 1103515245, !dbg !30
  %10 = add i32 %9, 12345, !dbg !30
  store i32 %10, i32* %seed, !dbg !31
  %11 = load i32, i32* %seed, !dbg !32
  %12 = sdiv i32 %11, 65536, !dbg !32
  %13 = srem i32 %12, 32768, !dbg !33
  store i32 %13, i32* %rand, !dbg !34
  %14 = load i32, i32* %j, !dbg !35
  %15 = getelementptr [512 x i32], [512 x i32]* %numbers, i32 0, i32 %14, !dbg !35
  %16 = load i32, i32* %rand, !dbg !36
  store i32 %16, i32* %15, !dbg !37
  br label %for.inc4, !dbg !37

for.inc4:                                         ; preds = %for.body3
  %17 = load i32, i32* %j, !dbg !38
  %18 = add i32 %17, 1, !dbg !38
  store i32 %18, i32* %j, !dbg !39
  br label %for.cond2, !dbg !39

for.end5:                                         ; preds = %for.cond2
  store i32 1, i32* %switches, !dbg !40
  br label %while.cond, !dbg !41

while.cond:                                       ; preds = %for.end10, %for.end5
  %19 = load i32, i32* %switches, !dbg !42
  %20 = icmp sgt i32 %19, 0, !dbg !42
  br i1 %20, label %while.body, label %while.end, !dbg !42

while.body:                                       ; preds = %while.cond
  store i32 0, i32* %switches, !dbg !43
  br label %for.init6, !dbg !44

while.end:                                        ; preds = %while.cond
  br label %for.inc, !dbg !45

for.init6:                                        ; preds = %while.body
  store i32 0, i32* %j, !dbg !46
  br label %for.cond7, !dbg !46

for.cond7:                                        ; preds = %for.inc9, %for.init6
  %21 = load i32, i32* %j, !dbg !47
  %22 = load i32, i32* %n, !dbg !48
  %23 = sub i32 %22, 1, !dbg !48
  %24 = icmp slt i32 %21, %23, !dbg !47
  br i1 %24, label %for.body8, label %for.end10, !dbg !47

for.body8:                                        ; preds = %for.cond7
  %25 = load i32, i32* %j, !dbg !49
  %26 = getelementptr [512 x i32], [512 x i32]* %numbers, i32 0, i32 %25, !dbg !49
  %27 = load i32, i32* %26, !dbg !50
  store i32 %27, i32* %a, !dbg !51
  %28 = load i32, i32* %j, !dbg !52
  %29 = add i32 %28, 1, !dbg !52
  %30 = getelementptr [512 x i32], [512 x i32]* %numbers, i32 0, i32 %29, !dbg !52
  %31 = load i32, i32* %30, !dbg !53
  store i32 %31, i32* %b, !dbg !54
  %32 = load i32, i32* %b, !dbg !55
  %33 = load i32, i32* %a, !dbg !56
  %34 = icmp slt i32 %32, %33, !dbg !55
  br i1 %34, label %if.then, label %if.else, !dbg !55

for.inc9:                                         ; preds = %if.end
  %35 = load i32, i32* %j, !dbg !57
  %36 = add i32 %35, 1, !dbg !57
  store i32 %36, i32* %j, !dbg !45
  br label %for.cond7, !dbg !45

for.end10:                                        ; preds = %for.cond7
  br label %while.cond, !dbg !45

if.then:                                          ; preds = %for.body8
  %37 = load i32, i32* %switches, !dbg !58
  %38 = add i32 %37, 1, !dbg !58
  store i32 %38, i32* %switches, !dbg !59
  %39 = load i32, i32* %j, !dbg !60
  %40 = getelementptr [512 x i32], [512 x i32]* %numbers, i32 0, i32 %39, !dbg !60
  %41 = load i32, i32* %b, !dbg !61
  store i32 %41, i32* %40, !dbg !62
  %42 = load i32, i32* %j, !dbg !63
  %43 = add i32 %42, 1, !dbg !63
  %44 = getelementptr [512 x i32], [512 x i32]* %numbers, i32 0, i32 %43, !dbg !63
  %45 = load i32, i32* %a, !dbg !64
  store i32 %45, i32* %44, !dbg !65
  br label %if.end, !dbg !65

if.else:                                          ; preds = %for.body8
  br label %if.end, !dbg !65

if.end:                                           ; preds = %if.else, %if.then
  br label %for.inc9, !dbg !65

for.init11:                                       ; preds = %for.end
  store i32 0, i32* %j, !dbg !66
  br label %for.cond12, !dbg !66

for.cond12:                                       ; preds = %for.inc14, %for.init11
  %46 = load i32, i32* %j, !dbg !67
  %47 = load i32, i32* %n, !dbg !68
  %48 = sub i32 %47, 1, !dbg !68
  %49 = icmp slt i32 %46, %48, !dbg !67
  br i1 %49, label %for.body13, label %for.end15, !dbg !67

for.body13:                                       ; preds = %for.cond12
  %50 = load i32, i32* %j, !dbg !69
  %51 = getelementptr [512 x i32], [512 x i32]* %numbers, i32 0, i32 %50, !dbg !69
  %52 = load i32, i32* %51, !dbg !70
  %53 = load i32, i32* %j, !dbg !71
  %54 = add i32 %53, 1, !dbg !71
  %55 = getelementptr [512 x i32], [512 x i32]* %numbers, i32 0, i32 %54, !dbg !71
  %56 = load i32, i32* %55, !dbg !72
  %57 = icmp sgt i32 %52, %56, !dbg !70
  br i1 %57, label %if.then16, label %if.else17, !dbg !70

for.inc14:                                        ; preds = %if.end18
  %58 = load i32, i32* %j, !dbg !73
  %59 = add i32 %58, 1, !dbg !73
  store i32 %59, i32* %j, !dbg !74
  br label %for.cond12, !dbg !74

for.end15:                                        ; preds = %for.cond12
  %60 = load i32, i32* %sorted, !dbg !75
  call void @echo(i32 %60), !dbg !75
  ret i32 0

if.then16:                                        ; preds = %for.body13
  store i32 0, i32* %sorted, !dbg !76
  br label %if.end18, !dbg !76

if.else17:                                        ; preds = %for.body13
  br label %if.end18, !dbg !76

if.end18:                                         ; preds = %if.else17, %if.then16
  br label %for.inc14, !dbg !76
}

attributes #0 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "Cheetah Compiler", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2)
!1 = !DIFile(filename: "bubble_sort.c", directory: "test")
!2 = !{}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 3, type: !5, isLocal: false, isDefinition: true, scopeLine: 3, flags: DIFlagPrototyped, isOptimized: false, unit: !0, retainedNodes: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7}
!7 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!8 = !DILocation(line: 3, column: 1, scope: !4)
!9 = !DILocation(line: 7, column: 1, scope: !4)
!10 = !DILocation(line: 8, column: 1, scope: !4)
!11 = !DILocation(line: 10, column: 1, scope: !4)
!12 = !DILocation(line: 12, column: 1, scope: !4)
!13 = !DILocation(line: 12, column: 8, scope: !4)
!14 = !DILocation(line: 13, column: 1, scope: !4)
!15 = !DILocation(line: 13, column: 8, scope: !4)
!16 = !DILocation(line: 14, column: 1, scope: !4)
!17 = !DILocation(line: 15, column: 1, scope: !4)
!18 = !DILocation(line: 17, column: 1, scope: !4)
!19 = !DILocation(line: 17, column: 6, scope: !4)
!20 = !DILocation(line: 17, column: 13, scope: !4)
!21 = !DILocation(line: 17, column: 17, scope: !4)
!22 = !DILocation(line: 19, column: 5, scope: !4)
!23 = !DILocation(line: 17, column: 33, scope: !4)
!24 = !DILocation(line: 17, column: 29, scope: !4)
!25 = !DILocation(line: 45, column: 1, scope: !4)
!26 = !DILocation(line: 46, column: 1, scope: !4)
!27 = !DILocation(line: 19, column: 10, scope: !4)
!28 = !DILocation(line: 19, column: 17, scope: !4)
!29 = !DILocation(line: 19, column: 21, scope: !4)
!30 = !DILocation(line: 21, column: 16, scope: !4)
!31 = !DILocation(line: 21, column: 9, scope: !4)
!32 = !DILocation(line: 22, column: 17, scope: !4)
!33 = !DILocation(line: 22, column: 16, scope: !4)
!34 = !DILocation(line: 22, column: 9, scope: !4)
!35 = !DILocation(line: 24, column: 17, scope: !4)
!36 = !DILocation(line: 24, column: 22, scope: !4)
!37 = !DILocation(line: 24, column: 9, scope: !4)
!38 = !DILocation(line: 19, column: 28, scope: !4)
!39 = !DILocation(line: 19, column: 24, scope: !4)
!40 = !DILocation(line: 28, column: 5, scope: !4)
!41 = !DILocation(line: 29, column: 5, scope: !4)
!42 = !DILocation(line: 29, column: 12, scope: !4)
!43 = !DILocation(line: 30, column: 9, scope: !4)
!44 = !DILocation(line: 32, column: 9, scope: !4)
!45 = !DILocation(line: 32, column: 30, scope: !4)
!46 = !DILocation(line: 32, column: 14, scope: !4)
!47 = !DILocation(line: 32, column: 21, scope: !4)
!48 = !DILocation(line: 32, column: 25, scope: !4)
!49 = !DILocation(line: 33, column: 25, scope: !4)
!50 = !DILocation(line: 33, column: 17, scope: !4)
!51 = !DILocation(line: 33, column: 13, scope: !4)
!52 = !DILocation(line: 34, column: 25, scope: !4)
!53 = !DILocation(line: 34, column: 17, scope: !4)
!54 = !DILocation(line: 34, column: 13, scope: !4)
!55 = !DILocation(line: 35, column: 17, scope: !4)
!56 = !DILocation(line: 35, column: 21, scope: !4)
!57 = !DILocation(line: 32, column: 34, scope: !4)
!58 = !DILocation(line: 36, column: 28, scope: !4)
!59 = !DILocation(line: 36, column: 17, scope: !4)
!60 = !DILocation(line: 37, column: 25, scope: !4)
!61 = !DILocation(line: 37, column: 30, scope: !4)
!62 = !DILocation(line: 37, column: 17, scope: !4)
!63 = !DILocation(line: 38, column: 25, scope: !4)
!64 = !DILocation(line: 38, column: 32, scope: !4)
!65 = !DILocation(line: 38, column: 17, scope: !4)
!66 = !DILocation(line: 46, column: 6, scope: !4)
!67 = !DILocation(line: 46, column: 13, scope: !4)
!68 = !DILocation(line: 46, column: 17, scope: !4)
!69 = !DILocation(line: 47, column: 17, scope: !4)
!70 = !DILocation(line: 47, column: 9, scope: !4)
!71 = !DILocation(line: 47, column: 30, scope: !4)
!72 = !DILocation(line: 47, column: 22, scope: !4)
!73 = !DILocation(line: 46, column: 26, scope: !4)
!74 = !DILocation(line: 46, column: 22, scope: !4)
!75 = !DILocation(line: 51, column: 6, scope: !4)
!76 = !DILocation(line: 48, column: 9, scope: !4)
