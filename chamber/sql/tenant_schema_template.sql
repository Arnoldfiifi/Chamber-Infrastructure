CREATE TABLE policies (
    policy_id UUID PRIMARY KEY,
    policy_version INT NOT NULL,
    policy_json JSONB NOT NULL,
    active BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT NOW()
);

CREATE TABLE routing_rules (
    rule_id UUID PRIMARY KEY,
    condition TEXT NOT NULL,
    target_model TEXT NOT NULL,
    confidence FLOAT,
    fallback_model TEXT,
    created_at TIMESTAMP DEFAULT NOW()
);

CREATE TABLE audit_log (
    trace_id UUID,
    decision JSONB,
    created_at TIMESTAMP DEFAULT NOW()
);

