import java.util.*

fun solve() {
    val sc = Scanner(System.`in`)
    if (!sc.hasNextInt()) return
    val t = sc.nextInt()
    repeat(t) {
        val k = sc.nextInt()
        val a1 = sc.nextInt()
        val b1 = sc.nextInt()
        val a2 = sc.nextInt()
        val b2 = sc.nextInt()

        val rA = (if (a1 > b1) 1 else 0) + (if (a2 > b2) 1 else 0)
        val rB = (if (b1 > a1) 1 else 0) + (if (b2 > a2) 1 else 0)
        val scoreA = a1 + a2
        val scoreB = b1 + b2

        var bobCanWin = false
        for (a3 in 0..k) {
            for (b3 in 0..k) {
                if (a3 == b3) continue
                
                val totalA = scoreA + a3
                val totalB = scoreB + b3
                val roundsA = rA + (if (a3 > b3) 1 else 0)
                val roundsB = rB + (if (b3 > a3) 1 else 0)
                
                if (totalB > totalA || (totalB == totalA && roundsB > roundsA)) {
                    bobCanWin = true
                    break
                }
            }
            if (bobCanWin) break
        }
        
        if (bobCanWin) println("YES") else println("NO")
    }
}

fun main() {
    solve()
}
