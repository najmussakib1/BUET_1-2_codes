import java.util.*

fun getP(n: Int): Int {
    var count = 0
    var temp = n
    var i = 2
    while (i * i <= temp) {
        while (temp % i == 0) {
            count++
            temp /= i
        }
        i++
    }
    if (temp > 1) count++
    return count
}

fun gcd(a: Int, b: Int): Int {
    var x = a
    var y = b
    while (y != 0) {
        x %= y
        val t = x
        x = y
        y = t
    }
    return x
}

fun solve() {
    val sc = Scanner(System.`in`)
    if (!sc.hasNextInt()) return
    val n = sc.nextInt()
    val m = sc.nextInt()
    val c = IntArray(m) { sc.nextInt() }

    val MOD = 998244353L

    val dist1 = IntArray(51) { getP(it) }
    val dist = Array(51) { u ->
        IntArray(51) { v ->
            dist1[u] + dist1[v] - 2 * dist1[gcd(u, v)]
        }
    }

    // dp[mask] = number of achievable arrays for current stage prefix
    // mask: bit j (0..8) is set if some index was last used at stage (current - 1 - j)
    var dp = LongArray(512)
    dp[0] = 1L

    for (i in 0 until m) {
        val nextDp = LongArray(512)
        val curC = c[i]
        val curP = dist1[curC]

        for (mask in 0 until 512) {
            if (dp[mask] == 0L) continue
            val ways = dp[mask]

            // Case 1: b[i] = 0
            val nextMask0 = (mask shl 1) and 511
            nextDp[nextMask0] = (nextDp[nextMask0] + ways) % MOD

            // Case 2: b[i] = k, where k was last used in one of stages i-1..i-9
            for (d in 1..9) {
                if (((mask shr (d - 1)) and 1) != 0) {
                    val prevC = c[i - d]
                    if (d >= dist[prevC][curC]) {
                        val nextMaskK = (((mask xor (1 shl (d - 1))) shl 1) or 1) and 511
                        nextDp[nextMaskK] = (nextDp[nextMaskK] + ways) % MOD
                    }
                }
            }

            // Case 3: b[i] = k, where k is "ready" (last used at j <= i-10 or never used)
            // Number of such indices is n - popcount(mask)
            if (i + 1 >= curP) {
                var popCount = 0
                for (j in 0..8) if (((mask shr j) and 1) != 0) popCount++
                
                val readyCount = n - popCount
                if (readyCount > 0) {
                    val nextMaskReady = ((mask shl 1) or 1) and 511
                    nextDp[nextMaskReady] = (nextDp[nextMaskReady] + ways * readyCount) % MOD
                }
            }
        }
        dp = nextDp
    }

    var total = 0L
    for (ways in dp) {
        total = (total + ways) % MOD
    }
    println(total)
}

fun main() {
    solve()
}
